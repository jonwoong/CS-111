/* 
CS 111
Jonathan Woong
804205763
W16 - Lab 1c
*/

///// HEADERS /////
#define _GNU_SOURCE

#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

///// USER DEFINED VALUES /////
static const int RDONLY = 1;
static const int WRONLY = 2;
static const int RDWR = 3;
static const int PIPE = 4;
static const int COMMAND = 5;
static const int WAIT = 6;
static const int CLOSE = 7;
static const int VERBOSE = 8;
static const int PROFILE = 9;
static const int ABORT = 10;
static const int CATCH = 11;
static const int IGNORE = 12;
static const int DEFAULT = 13;
static const int PAUSE = 14;

///// OPTION FLAGS /////
int verbose=0; 
int profile=0;

///// FILE OPEN FLAGS /////
int appendFlag=0;
int cloexecFlag=0;
int creatFlag=0;
int directoryFlag=0;
int dsyncFlag=0;
int exclFlag=0;
int nofollowFlag=0;
int nonblockFlag=0;
int rsyncFlag=0;
int syncFlag=0;
int truncFlag=0;

///// USER FUNCTIONS /////
void signalHandler(int signalNumber){ // used in --catch
	fprintf(stderr, "%d caught\n", signalNumber);
	exit(signalNumber);
}
void clearFlags(){ // clears open-time flags
	appendFlag=0; 
	cloexecFlag=0; 
	creatFlag=0;
	directoryFlag=0;
	dsyncFlag=0; 
	exclFlag=0; 
	nofollowFlag=0;
	nonblockFlag=0; 
	rsyncFlag=0; 
	syncFlag=0;
	truncFlag=0;
}
void verboseFlags(){ // verbose flags if they are set
	if (appendFlag){
		fputs(" --append",stdout);
	}
	if (cloexecFlag){
		fputs(" --cloexec",stdout);
	}
	if (creatFlag){
		fputs(" --creat",stdout);
	}
	if (directoryFlag){
		fputs(" --directory",stdout);
	}
	if (dsyncFlag){
		fputs(" --dsync",stdout);
	}
	if (exclFlag){
		fputs(" --excl",stdout);
	}
	if (nofollowFlag){
		fputs(" --nofollow",stdout);
	}
	if (nonblockFlag){
		fputs(" --nonblock",stdout);
	}
	if (rsyncFlag){
		fputs(" --rsync",stdout);
	}
	if (syncFlag){
		fputs(" --sync",stdout);
	}
	if(truncFlag){
		fputs(" --trunc",stdout);
	}
}

///// USER STRUCTS /////
struct childProcessStruct { // tracks child pid, number of subcommand args, and actual arg strings
	pid_t childPid;
	int numberOfCommandAndArgs;
	char* commandAndArgs[100];
};

///// MAIN FUNCTION /////
int main(int argc, char *argv[]){

	///// VARIABLES /////
	int attemptToReuseClosedFd=0; // flag (0=NO, 1=YES)
	int valueReturnedByGetOpt=0; // used to identify options in switch statement
	int fileFd=0; // real fd of a file
	int numberOfFds=0; // number of fds in fdArray
	int numberOfClosedFds=0; // number of fds closed by --close
	int childExitStatus=0; // used by parent process
	int numberOfChildrenForked=0; // used by wait
	int numberOfChildrenThatExited=0; // used by wait
	char *fileName = NULL; // filename
	int argCounter=0; // keeps track of how many arguments are specified after a subcommand
	int simpshExitStatus=0; // exit status of simpsh
	int programIsFinished=0; // flag (0=NO, 1=YES) set by --wait
	struct rusage parentStart;
	struct rusage parentEnd;
	struct rusage childrenStart;
	struct rusage childrenEnd;
	long parentUserModeSeconds=0;
	long parentUserModeMicroSeconds=0;
	long parentKernelModeSeconds=0;
	long parentKernelModeMicroSeconds;
	long childrenUserModeSeconds=0;
	long childrenUserModeMicroSeconds=0;
	long childrenKernelModeSeconds=0;
	long childrenKernelModeMicroSeconds=0;

	///// ARRAYS /////
	int *fdArray=NULL; // dynamically allocated array used to hold fd's 
	int *closedFdArray = NULL; // dynamic array to hold closed fd's
	struct childProcessStruct *childrenArray = NULL; // dynamic array to track child process data

	while (!programIsFinished)
	{
		///// OPTIONS //////
		struct option long_options[] =
		{
			///// FILE FLAGS /////
			{"append",		no_argument, &appendFlag, O_APPEND},
			{"cloexec", 	no_argument, &cloexecFlag, O_CLOEXEC},
			{"creat", 		no_argument, &creatFlag, O_CREAT},
			{"directory", 	no_argument, &directoryFlag, O_DIRECTORY},
			{"dsync", 		no_argument, &dsyncFlag, O_DSYNC},
			{"excl", 		no_argument, &exclFlag, O_EXCL},
			{"nofollow",	no_argument, &nofollowFlag, O_NOFOLLOW},
			{"nonblock",	no_argument, &nonblockFlag, O_NONBLOCK},
			{"rsync",		no_argument, &rsyncFlag, O_RSYNC},
			{"sync",		no_argument, &syncFlag, O_SYNC},
			{"trunc",		no_argument, &truncFlag, O_TRUNC},
			///// FILE OPENING /////
			{"rdonly", 		required_argument, 0, RDONLY},
			{"wronly", 		required_argument, 0, WRONLY},
			{"rdwr",		required_argument, 0, RDWR},
			{"pipe",		no_argument, 0, PIPE},
			///// SUBCOMMAND /////
			{"command", 	required_argument, 0, COMMAND},
			{"wait",		no_argument, 0, WAIT},
			///// MISC /////
			{"close", 		required_argument, 0, CLOSE},
			{"verbose", 	no_argument, 0, VERBOSE},
			{"profile", 	no_argument, 0, PROFILE},
			{"abort", 		no_argument, 0, ABORT},
			{"catch",		required_argument, 0, CATCH},
			{"ignore",		required_argument, 0, IGNORE},
			{"default",		required_argument, 0, DEFAULT},
			{"pause",		no_argument, 0, PAUSE},
			{0,0,0,0}
		};
		int option_index = 0;
		valueReturnedByGetOpt = getopt_long(argc,argv,"",long_options,&option_index);
		// valueReturnedByGetOpt corresponds to the global values above

		///// ERROR CHECKING /////
		if (valueReturnedByGetOpt == -1) { 
			break;
		}

		///// UPDATING FD TABLE ARRAY /////
		// If --rdonly, --wronly, or --rdwr is called, the fd table array size must be created or extended to fit the opened fd's 
		if (valueReturnedByGetOpt == 1 || valueReturnedByGetOpt == 2 || valueReturnedByGetOpt == 3) { // if user inputs --rdonly or --wronly or --rdwr
			// create fd table if no files have been opened yet
			if (fdArray==NULL) { 
				fdArray = (int *)malloc(sizeof(int)); // allocate enough memory for 1 fd
			}
			// extend fd table if previous files have already been opened
			else { 
				fdArray = realloc(fdArray, (numberOfFds+1)*sizeof(int)); // resize to fit exactly one more fd
			}
		}
		// If --pipe is called, the fd array must either be created or extended by 2
		if (valueReturnedByGetOpt == 4) { // if user inputs --pipe
			// array creation
			if (fdArray==NULL) {
				fdArray = (int*)malloc(2*sizeof(int)); // allocate space for 2 fd's (read and write end)
			}
			else { // array expansion
				fdArray = realloc(fdArray, (numberOfFds+2)*sizeof(int));
			}
		}

		///// UPDATING CLOSED FD ARRAY /////
		// If --close is called, the closed fd must be tracked to ensure that the closed fd is not opened again
		if (valueReturnedByGetOpt == 7) { // if user inputs --close
			// array creation
			if (closedFdArray==NULL) {
				closedFdArray = (int *)malloc(sizeof(int));
			}
			else { // array expansion
				closedFdArray = realloc(closedFdArray, (numberOfClosedFds+1)*sizeof(int));
			}
		}

		///// UPDATING CHILD ARRAY /////
		// If --command is called, the children that are forked must be tracked
		if (valueReturnedByGetOpt ==5) // if user inputs --command
		{
			// array creation
			if (childrenArray==NULL){
				childrenArray = malloc(sizeof * childrenArray);
			}
			else{ // array expansion
				childrenArray = realloc(childrenArray, (numberOfChildrenForked+1)*sizeof*childrenArray);
			}
		}

		///// SWITCH STATEMENTS /////
		switch(valueReturnedByGetOpt)
		{
			case 0:
				break;

			///// --RDONLY /////
			case 1: // --rdonly
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
				}

				fileName = optarg;

				///// VERBOSE /////
				if (verbose) {
					verboseFlags();
					fprintf(stdout, "--rdonly %s\n",fileName);
				}

				///// OPENING FILE /////
				fileFd = open(fileName,O_RDONLY|appendFlag|cloexecFlag|creatFlag|directoryFlag|dsyncFlag|exclFlag|nofollowFlag|nonblockFlag|rsyncFlag|syncFlag|truncFlag,0777);
				clearFlags();

				///// ERROR CHECKING /////
				if (fileFd==-1) { // check if file could not be opened
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				for (int i=0; i<numberOfClosedFds; i++) { // check if attempting to open a closed fd
					if (fileFd == closedFdArray[i]) {
						fputs("rdonly attempted to reuse a closed file descriptor \n",stderr);
						attemptToReuseClosedFd=1; // set flag
					}
				}
				if(attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				///// UPDATE FD ARRAY /////
				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process rdonly took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process rdonly took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			///// --WRONLY /////
			case 2: // --wronly
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF, &parentStart);
				}

				fileName = optarg;

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout, "--wronly %s\n",fileName);
				///// OPENING FILE /////
				fileFd = open(fileName,O_WRONLY|appendFlag|cloexecFlag|creatFlag|directoryFlag|dsyncFlag|exclFlag|nofollowFlag|nonblockFlag|rsyncFlag|syncFlag|truncFlag,0777);
				clearFlags();
				///// ERROR CHECKING /////
				if (fileFd==-1) { // check if file could not be opened
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				for (int i=0; i<numberOfClosedFds; i++) { // check if attempting to open a closed fd
					if (fileFd == closedFdArray[i]) {
						fputs("wronly attempted to reuse a closed file descriptor \n",stderr);
						attemptToReuseClosedFd=1; // set flag
					}
				}
				if(attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				///// UPDATE FD ARRAY /////
				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process wronly took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process wronly took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			////// --RDWR /////
			case 3: // --rdwr
			{
				///// PROFILE /////
				if (profile) {
					getrusage(RUSAGE_SELF,&parentStart);
				}

				fileName = optarg;

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout, "--rdwr %s\n",fileName);

				///// OPENING FILE /////
				fileFd = open(fileName,O_RDWR|appendFlag|cloexecFlag|creatFlag|directoryFlag|dsyncFlag|exclFlag|nofollowFlag|nonblockFlag|rsyncFlag|syncFlag|truncFlag,0777);
				clearFlags();

				///// ERROR CHECKING /////
				if (fileFd==-1) { // check if file could not be opened
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				for (int i=0; i<numberOfClosedFds; i++) { // check if attempting to open a closed fd
					if (fileFd == closedFdArray[i]) {
						fputs("rdwr attempted to reuse a closed file descriptor \n",stderr);
						attemptToReuseClosedFd=1; // set flag
					}
				} 
				if(attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				///// UPDATE FD ARRAY /////
				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process rdwr took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process rdwr took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			///// --PIPE //////
			case 4: // --pipe
			{
				///// PROFILE /////
				if (profile) {
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// CREATE PIPE /////
				int pipeFd[2];
				if (pipe(pipeFd)==-1){
					fputs("Could not create pipe\n",stderr);
				}

				///// UPDATE FD ARRAY /////
				fdArray[numberOfFds] = pipeFd[0]; // read end
				numberOfFds++;
				fdArray[numberOfFds] = pipeFd[1]; // write end
				numberOfFds++;

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process pipe took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process pipe took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}
				
				break;
			}

			////// --COMMAND //////
			case 5: // --command
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
				}

				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument

				///// VERBOSE /////
				if (verbose)
				{
					fputs("--command",stdout);
					for (int i=optind;i<optind+3;i++){ // cmd's I O E
						fprintf(stdout," %s",argv[i]); // print I O E
					}
					fprintf(stdout," %s",argv[optind+3]); // print name of command
				}

				///// COUNT NUMBER OF CMD ARGS /////
				for (int i=optind+4;i<argc;i++) { // count # of args after command
					if (argv[i][0]=='-'&&argv[i][1]=='-') // break if encounter "--"" when looping through args
						break;
					if (verbose)
						fprintf(stdout, " %s",argv[i]); // print args
					argCounter++;
				}

				///// CREATE CMD ARG BUFFER /////
				char* arg[argCounter+1]; // contains [subcmd,arg1,arg2,...]
				arg[0] = argv[optind+3]; // arg[0] = "subcmd"

				if (verbose)
					fputs("\n",stdout); // add newline for next option

				int k=1; 
				if (argCounter > 0)
				{
					for (int i=optind+4;i<argc;i++) { // args after subcommand
						if (argv[i][0]=='-'&&argv[i][1]=='-') // if encounter -- when looping through args
							break;

						arg[k] = argv[i]; // place args into arg array
						k++;
					}
					arg[argCounter+1] = NULL; // last arg = NULL
				}
				else{
					arg[1] = NULL; // no args
				}

				///// CHECK CMD FD's FOR ERRORS /////
				if (fdArray==NULL) {
					fputs("No file descriptors have been created\n",stderr);
				}
				if (fdArray[atoi(argv[optind])] <=0 ) { // check cmd's stdin
					fprintf(stderr, "Incorrect STDIN file descriptor index specified by %s\n",arg[0]);
					break;
				}
				if (fdArray[atoi(argv[optind+1])] <= 0 ) { // check cmd's stdout
					fprintf(stderr, "Incorrect STDOUT file descriptor index specified by %s\n",arg[0]);
					break;
				}
				if (fdArray[atoi(argv[optind+2])] <= 0 ) { // check cmd's stderr
					fprintf(stderr, "Incorrect STDERR file descriptor index specified by %s\n",arg[0]);
					break;
				}
				for (int i=0;i<numberOfClosedFds;i++){ // check if attempting to reuse a closed fd
					if (fdArray[atoi(argv[optind])] == closedFdArray[i] ||
						fdArray[atoi(argv[optind+1])] == closedFdArray[i] ||
						fdArray[atoi(argv[optind+2])] == closedFdArray[i]) {
						fprintf(stderr, "%s attempted to reuse a closed file descriptor\n",arg[0]);
						attemptToReuseClosedFd=1; // set flag
					}
				}
				if (attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				///// SUBPROCESS /////
				pid_t forkValue = fork(); // forkValue == 0 for child, forkValue > 0 for parent

				if (forkValue < 0) { // check if child could not be forked
					fputs("Could not fork child process\n",stderr);
					exit(0);
				}
				else if (forkValue == 0){ // child process					
					///// DUP2 /////
					dup2(fdArray[atoi(argv[optind])],0); // STDIN
					dup2(fdArray[atoi(argv[optind+1])],1); // STDOUT
					dup2(fdArray[atoi(argv[optind+2])],2); // STDERR

					///// CLOSE ALL FDs /////
					for (int i=0; i<numberOfFds; i++) {
						close(fdArray[i]);
					}

					///// EXECUTE
					execvp(arg[0],arg); // execute subcommand
					fprintf(stderr, "Could not execute command %s\n",argv[optind+3]); // if this point is reached, execvp failed
					simpshExitStatus=1; // set exit status of program if child reaches this point
					_exit(1);
				}
				else if (forkValue > 0) // parent process
				{
					///// CHILD PROCESS TRACKING /////
					childrenArray[numberOfChildrenForked].childPid = forkValue; // track child PID that must be waited on later
					childrenArray[numberOfChildrenForked].numberOfCommandAndArgs = argCounter+1; // track number of args (including the command)
					for (int i=0; i<argCounter+1; i++) { // track command arguments that child process executed
						childrenArray[numberOfChildrenForked].commandAndArgs[i] = arg[i];
					}
					numberOfChildrenForked++; // increment number of children 

					///// CLOSE FDs / PIPE ENDS /////
					close(fdArray[atoi(argv[optind])]); // close STDIN
					close(fdArray[atoi(argv[optind+1])]); // close STDOUT
					close(fdArray[atoi(argv[optind+2])]); // close STDERR
				}

				///// PROFILE /////
				if(profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process %s took %ld.%ld seconds in usermode\n", arg[0], parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process %s took %ld.%ld seconds in kernelmode\n", arg[0], parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}
				break;
			}

			///// --WAIT /////
			case 6: // --wait
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
					getrusage(RUSAGE_CHILDREN,&childrenStart);
				}

				///// VERBOSE /////
				if (verbose)
					fputs("--wait\n",stdout);

				///// CLOSE ALL FDs /////
				for (int i=0; i<numberOfFds; i++) {
					close(fdArray[i]);
				}

				///// CHILD REAPING /////
				do { 
					int childExitStatus; // exit status of child
					pid_t childPidThatExited; // pid of child that exits
					childPidThatExited = waitpid(-1, &childExitStatus, 0); // pid of reaped child

					for(int i=0; i<numberOfChildrenForked; i++) // loop through all children to obtain info about the child that was reaped above
					{
						if (childrenArray[i].childPid == childPidThatExited) { // matched reaped child pid with an entry in childrenArray
							if (WIFEXITED(childExitStatus)){ // if child exits successfully
								fprintf(stdout, "%d", WEXITSTATUS(childExitStatus)); // print exit status
							}
							else { // if child exits with a non-zero status
								if (childExitStatus > simpshExitStatus){
									simpshExitStatus = childExitStatus; // simpsh will exit with the largest non-zero status
								}
							}
							for (int k=0; k<childrenArray[i].numberOfCommandAndArgs; k++) {
								fprintf(stdout, " %s", childrenArray[i].commandAndArgs[k]); // print child command and args
							}
							fputs("\n",stdout); // newline for next output
							numberOfChildrenThatExited++; // increment number of reaped children
							break;
						}
					}
				} while (numberOfChildrenThatExited!=numberOfChildrenForked); // exit the do-while loop when all children have been reaped
				programIsFinished=1; // program is done

				///// PROFILE /////
				if(profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					getrusage(RUSAGE_CHILDREN,&childrenEnd);
					parentUserModeSeconds += (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds += (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds += (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds += (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					childrenUserModeSeconds += (childrenEnd.ru_utime.tv_sec - childrenStart.ru_utime.tv_sec);
					childrenUserModeMicroSeconds += (childrenEnd.ru_utime.tv_usec - childrenStart.ru_utime.tv_usec);
					childrenKernelModeSeconds += (childrenEnd.ru_stime.tv_sec - childrenStart.ru_stime.tv_sec);
					childrenKernelModeMicroSeconds += (childrenEnd.ru_stime.tv_usec - childrenStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent took %ld.%ld seconds to reap in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent took %ld.%ld seconds to reap in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
					fprintf(stdout,"Children took %ld.%ld seconds in usermode\n", childrenUserModeSeconds, childrenUserModeMicroSeconds);
					fprintf(stdout,"Children took %ld.%ld seconds in kernelmode\n", childrenKernelModeSeconds, childrenKernelModeMicroSeconds);
				}
				break;
			}

			///// --CLOSE /////
			case 7: // --close
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout,"--close %d\n",atoi(argv[optind-1]));

				///// CLOSE + UPDATE ARRAY //////
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				close(fdArray[atoi(argv[optind])]); // close specified fd
				closedFdArray[numberOfClosedFds] = fdArray[atoi(argv[optind])]; // track closed fd (add closed fd to array)
				numberOfClosedFds++; // increment array size

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process close took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process close took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}
				break;
			}

			///// --VERBOSE /////
			case 8: // --verbose
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose) // if verbose was already set
					fputs("--verbose\n",stdout);
				else
					verbose=1; // set flag if first time calling verbose

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process verbose took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process verbose took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}
				break;
			}

			///// --PROFILE /////
			case 9: // --profile
			{
				///// VERBOSE /////
				if (verbose)
					fputs("--profile\n",stdout);

				///// PROFILE /////
				profile=1; // set flag if first time calling profile

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process profile took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process profile took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break; // not implemented in 1b
			}

			///// --ABORT /////
			case 10: // --abort
			{
				///// PROFILE /////
				if (profile) {
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose)
					fputs("--abort\n",stdout);

				///// ABORT /////
				int abortSignal; 
				abortSignal = raise(SIGSEGV); // causes seg fault

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process abort took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process abort took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			///// --CATCH /////
			case 11: // --catch
			{
				///// PROFILE /////
				if (profile) {
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout,"--catch %d\n",atoi(argv[optind-1]));

				///// CATCH /////
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				signal(atoi(argv[optind]),signalHandler); // catch signal

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process catch %d took %ld.%ld seconds in usermode\n", atoi(argv[optind]), parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process catch %d took %ld.%ld seconds in kernelmode\n", atoi(argv[optind]), parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			///// --IGNORE /////
			case 12: // --ignore
			{
				///// PROFILE /////
				if (profile) {
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout,"--ignore %d\n",atoi(argv[optind-1]));

				///// IGNORE /////
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				signal(atoi(argv[optind]),SIG_IGN); // ignore signal

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process ignore %d took %ld.%ld seconds in usermode\n", atoi(argv[optind]), parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process ignore %d took %ld.%ld seconds in kernelmode\n", atoi(argv[optind]), parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}
				break;
			}

			///// --DEFAULT /////
			case 13: // --default
			{
				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout,"--default %d\n",atoi(argv[optind-1]));

				///// DEFAULT /////
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				signal(atoi(argv[optind]),SIG_DFL); // default behavior

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process default %d took %ld.%ld seconds in usermode\n", atoi(argv[optind]), parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process default %d took %ld.%ld seconds in kernelmode\n", atoi(argv[optind]), parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			///// --PAUSE /////
			case 14: // --pause
			{
				///// PROFILE /////
				if (profile) {
					getrusage(RUSAGE_SELF,&parentStart);
				}

				///// VERBOSE /////
				if (verbose)
					fputs("--pause\n",stdout);

				///// PAUSE /////
				pause();

				///// PROFILE /////
				if (profile){
					getrusage(RUSAGE_SELF,&parentEnd);
					parentUserModeSeconds = (parentEnd.ru_utime.tv_sec - parentStart.ru_utime.tv_sec);
					parentUserModeMicroSeconds = (parentEnd.ru_utime.tv_usec - parentStart.ru_utime.tv_usec);
					parentKernelModeSeconds = (parentEnd.ru_stime.tv_sec - parentStart.ru_stime.tv_sec);
					parentKernelModeMicroSeconds = (parentEnd.ru_stime.tv_usec - parentStart.ru_stime.tv_usec);
					fprintf(stdout,"Parent process pause took %ld.%ld seconds in usermode\n", parentUserModeSeconds, parentUserModeMicroSeconds);
					fprintf(stdout,"Parent process pause took %ld.%ld seconds in kernelmode\n", parentKernelModeSeconds, parentKernelModeMicroSeconds);
				}

				break;
			}

			///// DEFAULT /////
			default:
			{
				fputs("No option specified",stderr);
				break;
			}
		}
	}

	///// CLEAR DYNAMIC ARRAYS /////
	free(fdArray); 
	free(closedFdArray);
	free(childrenArray);

	///// RETURN //////
	exit(simpshExitStatus);
}
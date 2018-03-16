/* 
CS 111
Jonathan Woong
804205763
S16 - Lab 1b
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

///// USER FUNCTIONS /////
void signalHandler(int signalNumber){
	fprintf(stderr, "%d caught\n", signalNumber);
	exit(signalNumber);
}

///// USER STRUCTS /////
struct childProcessStruct {
	pid_t childPid;
	int numberOfCommandAndArgs;
	char* commandAndArgs[20];
};

///// MAIN FUNCTION /////
int main(int argc, char *argv[]){

	///// VARIABLES /////
	int valueReturnedByGetOpt=0; // used to identify options
	int fileFd=0; // real fd of a file
	int numberOfFds=0; // number of fds in fdArray
	int numberOfClosedFds=0; // number of fds closed by --close
	int verbose=0; // flag (0=OFF, 1=ON)
	int attemptToReuseClosedFd=0; // flag (0=NO, 1=YES)
	int childExitStatus=0; // used by parent process
	int numberOfChildrenForked=0; // used by wait
	int numberOfChildrenThatExited=0; // used by wait
	char *fileName = NULL; // filename

	///// FLAGS /////
	int appendFlag=0;
	int cloexecFlag=0;
	int creatFlag=0;
	int directoryFlag=0;
	int dsyncFlag=0;
	int execlFlag=0;
	int nofollowFlag=0;
	int nonblockFlag=0;
	int rsyncFlag=0;
	int syncFlag=0;
	int truncFlag=0;

	///// ARRAYS /////
	int *fdArray=NULL; // dynamically allocated array used to hold fd's 
	int *closedFds = NULL; // dynamic array to hold closed fd's
	struct childProcessStruct *children = NULL; // dynamic array to hold childPid and associated command (array of structs)

	while (1)
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
			{"execl", 		no_argument, &execlFlag, O_EXCL},
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
		// valueReturnedByGetOpt will be 1,2,3, or 4 and corresponds to the global values above

		if (valueReturnedByGetOpt == -1) { // while loop end condition
			break;
		}

		///// UPDATING FD ARRAY /////
		if (valueReturnedByGetOpt == 1 || valueReturnedByGetOpt == 2 || valueReturnedByGetOpt == 3) // if user inputs --rdonly or --wronly or --rdwr
		{
			// an fd table must either be created or extended
			if (fdArray==NULL) { // if there are no current fd's in the fd table, create an fd table
				fdArray = (int *)malloc(sizeof(int)); // allocate enough memory for 1 fd
			}
			else { // if adding an fd to an existing table
				fdArray = realloc(fdArray, (numberOfFds+1)*sizeof(int)); // resize to fit exactly one more fd
			}
		}
		if (valueReturnedByGetOpt == 4) // if user inputs --pipe
		{
			// array creation
			if (fdArray==NULL) {
				fdArray = (int*)malloc(2*sizeof(int)); // allocate space for 2 fd's (read and write end)
			}
			else { // array expansion
				fdArray = realloc(fdArray, (numberOfFds+2)*sizeof(int));
			}
		}
		///// UPDATING CLOSED FD ARRAY /////
		if (valueReturnedByGetOpt == 7) // if user inputs --close
		{
			// array creation
			if (closedFds==NULL) {
				closedFds = (int *)malloc(sizeof(int));
			}
			else { // array expansion
				closedFds = realloc(closedFds, (numberOfClosedFds+1)*sizeof(int));
			}
		}
		///// UPDATING CHILD ARRAY /////
		if (valueReturnedByGetOpt ==5) // if user inputs --command
		{
			// array creation
			if (children==NULL){
				children = malloc(10 * sizeof * children);
			}
			else{
				children = realloc(children, (numberOfChildrenForked+1)*sizeof*children);
			}
		}

		///// SWITCH STATEMENTS /////
		int argCounter=0; // keeps track of how many arguments are specified after a command
		switch(valueReturnedByGetOpt)
		{
			case 0:
				break;
			case 1: // --rdonly
			{
				fileName = optarg;

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout, "--rdonly %s\n",fileName);

				///// OPENING FILE /////
				fileFd = open(fileName,O_RDONLY);

				///// ERROR CHECKING /////
				if (fileFd==-1) {
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				for (int i=0; i<numberOfClosedFds; i++) {
					if (fileFd == closedFds[i]) {
						fputs("rdonly attempted to reuse a closed file descriptor \n",stderr);
						attemptToReuseClosedFd=1;
					}
				}
				if(attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;

				break;
			}
			case 2: // --wronly
			{
				fileName = optarg;

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout, "--wronly %s\n",fileName);

				///// OPENING FILE /////
				fileFd = open(fileName,O_WRONLY);

				///// ERROR CHECKING /////
				if (fileFd==-1) {
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				for (int i=0; i<numberOfClosedFds; i++) {
					if (fileFd == closedFds[i]) {
						fputs("wronly attempted to reuse a closed file descriptor \n",stderr);
						attemptToReuseClosedFd=1;
					}
				}
				if(attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;

				break;
			}
			case 3: // --rdwr
			{
				fileName = optarg;

				///// VERBOSE /////
				if (verbose)
					fprintf(stdout, "--rdwr %s\n",fileName);

				///// OPENING FILE /////
				fileFd = open(fileName,O_RDWR);

				///// ERROR CHECKING /////
				if (fileFd==-1) {
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				for (int i=0; i<numberOfClosedFds; i++) {
					if (fileFd == closedFds[i]) {
						fputs("rdwr attempted to reuse a closed file descriptor \n",stderr);
						attemptToReuseClosedFd=1;
					}
				}
				if(attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;
				break;
			}
			case 4: // --pipe
			{
				int pipeFd[2];
				if (pipe(pipeFd)==-1){
					fputs("Could not create pipe\n",stderr);
				}
				fdArray[numberOfFds] = pipeFd[0];
				fdArray[numberOfFds+1] = pipeFd[1];
				numberOfFds+=2;
				break;
			}
			case 5: // --command
			{
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

				///// COUNT CMD ARGS /////
				for (int i=optind+4;i<argc;i++) { // count # of args after command
					if (argv[i][0]=='-'&&argv[i][1]=='-') // if encounter -- when looping through args
						break;
					if (verbose)
						fprintf(stdout, " %s",argv[i]); // print args

					argCounter++;
				}

				///// CREATE CMD ARG BUFFER /////
				char* arg[argCounter+1]; // contains [cmd,arg1,arg2,...]
				arg[0] = argv[optind+3]; // arg[0] = "cmd"

				if (verbose)
					fputs("\n",stdout); // add newline for next option

				int k=1; 
				if (argCounter > 0)
				{
					for (int i=optind+4;i<argc;i++) { // args after command
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
				if (fdArray==NULL)
				{
					fputs("No file descriptors have been created\n",stderr);
				}
				if (fdArray[atoi(argv[optind])] <=0 ) { // check cmd's stdin
					fputs("Error reading input fd\n",stderr);
					break;
				}
				if (fdArray[atoi(argv[optind+1])] <= 0 ) { // check cmd's stdout
					fputs("Error reading output fd\n",stderr);
					break;
				}
				if (fdArray[atoi(argv[optind+2])] <= 0 ) { // check cmd's stderr
					fputs("Error reading error fd\n",stderr);
					break;
				}
				for (int i=0;i<numberOfClosedFds;i++){ // check if attempting to reuse a closed fd
					if (fdArray[atoi(argv[optind])] == closedFds[i] ||
						fdArray[atoi(argv[optind+1])] == closedFds[i] ||
						fdArray[atoi(argv[optind+2])] == closedFds[i]) {
						fprintf(stderr, "%s attempted to reuse a closed file descriptor\n",arg[0]);
						attemptToReuseClosedFd=1;
					}
				}
				if (attemptToReuseClosedFd) {
					attemptToReuseClosedFd=0; // reset
					break;
				}

				///// SUBPROCESS /////
				pid_t forkValue = fork();
				pid_t wait;

				if (forkValue < 0) {
					fputs("Could not fork child process\n",stderr);
					exit(0);
				}
				else if (forkValue == 0){ // child process
					///// DUP2 /////
					dup2(fdArray[atoi(argv[optind])],0); // STDIN
					dup2(fdArray[atoi(argv[optind+1])],1); // STDOUT
					dup2(fdArray[atoi(argv[optind+2])],2); // STDERR

					///// CLOSE PIPE ENDS /////
					close(fdArray[atoi(argv[optind])]); // close stdin
					close(fdArray[atoi(argv[optind+1])]); // close stdout
					close(fdArray[atoi(argv[optind+2])]); // close stderr

					///// EXECUTE
					execvp(arg[0],arg);
					fprintf(stderr, "Could not execute command %s\n",argv[optind+3]); // if this point is reached, execvp failed
					exit(1);
				}
				else if (forkValue > 0) // parent process
				{
					///// CHILD PROCESS TRACKING /////
					children[numberOfChildrenForked].childPid = forkValue; // track child PID that must be waited on later
					children[numberOfChildrenForked].numberOfCommandAndArgs = argCounter+1; // used in wait
					for (int i=0; i<argCounter+1; i++) { // track arguments that child process executed
						children[numberOfChildrenForked].commandAndArgs[i] = arg[i];
					}
					numberOfChildrenForked++; // track number of children

					///// CLOSE PIPE ENDS /////
					close(fdArray[atoi(argv[optind])]); // close STDIN
					close(fdArray[atoi(argv[optind+1])]); // close STDOUT
					close(fdArray[atoi(argv[optind+2])]); // close STDERR
				}
				break;
			}
			case 6: // wait
			{
				do {
					int childExitStatus; // exit status of child
					pid_t childPidThatExited; // pid of child that exits
					childPidThatExited = waitpid(-1, &childExitStatus, 0); // pid of reaped child

					for(int i=0; i<numberOfChildrenForked; i++) // loop through all children to obtain info about the child that was reaped above
					{
						if (children[i].childPid == childPidThatExited) { 
							if (WIFEXITED(childExitStatus)){ // if child exits successfully
								fprintf(stdout, "%d", WEXITSTATUS(childExitStatus)); // print exit status
							}
							for (int k=0; k<children[i].numberOfCommandAndArgs; k++) {
								fprintf(stdout, " %s", children[i].commandAndArgs[k]); // print child command and args
							}
							fputs("\n",stdout); // newline for next output
							numberOfChildrenThatExited++;
							break;
						}
					}
				} while (numberOfChildrenThatExited!=numberOfChildrenForked); // exit the do-while loop when all children have exited
				break;
			}
			case 7: // close
			{
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				close(fdArray[atoi(argv[optind])]); // close specified fd
				closedFds[numberOfClosedFds] = fdArray[atoi(argv[optind])]; // add closed fd to array
				numberOfClosedFds++; // increment array size
				break;
			}
			case 8: // verbose
			{
				if (verbose) // if verbose was already set
					fputs("--verbose\n",stdout);
				else
					verbose=1;
				break;
			}
			case 9: // profile
			{
				break;
			}
			case 10: // abort
			{
				int abortSignal;
				abortSignal = raise(SIGSEGV); // causes seg fault
				break;
			}
			case 11: // catch
			{
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				signal(atoi(argv[optind]),signalHandler); // catch signal
				break;
			}
			case 12: // ignore
			{
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				signal(atoi(argv[optind]),SIG_IGN); // ignore signal
				break;
			}
			case 13: // default
			{
				optind--; // optind points to 2nd argument by default, so decrement to point to 1st argument
				signal(atoi(argv[optind]),SIG_DFL); // default behavior
				break;
			}
			case 14: // pause
			{
				pause();
				break;
			}
			default:
				break;
		}
	}
	free(fdArray); // clear any dynamically allocated array
	free(closedFds);
	return 0;
}
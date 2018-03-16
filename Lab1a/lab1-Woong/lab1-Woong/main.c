/* 
CS 111
Jonathan Woong
804205763
S16 - Lab 1a
*/

///// HEADERS /////
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

///// USER DEFINED VALUES /////
const int RDONLY = 1;
const int WRONLY = 2;
const int COMMAND = 3;
const int VERBOSE = 4;

int main(int argc, char *argv[]){

	///// USER DEFINED VALUES /////
	int valueReturnedByGetOpt=0; // will be 1, 2, 3 or 4
	char *fileName = NULL; 
	int fileFd=0; // real fd of a file
	int *fdArray=NULL; // dynamically allocated array used to hold fd's 
	int numberOfFds=0; 
	int verbose=0; // flag (0=OFF, 1=ON)
	int returnStatus=0;

	while (1)
	{
		///// OPTIONS //////
		struct option long_options[] =
		{
			{"rdonly", required_argument, 0, RDONLY},
			{"wronly", required_argument, 0, WRONLY},
			{"command", required_argument, 0, COMMAND},
			{"verbose", no_argument, 0, VERBOSE},
			{0,0,0,0}
		};
		int option_index = 0;
		valueReturnedByGetOpt = getopt_long(argc,argv,"",long_options,&option_index);
		// valueReturnedByGetOpt will be 1,2,3, or 4 and corresponds to the global values above

		if (valueReturnedByGetOpt == -1) { // while loop end condition
			break;
		}

		///// UPDATING FD ARRAY /////
		if (valueReturnedByGetOpt == 1 || valueReturnedByGetOpt == 2) // if user inputs --rdonly or --wronly
		{
			// an fd table must either be created or extended
			if (fdArray==NULL) { // if there are no current fd's in the fd table, create an fd table
				fdArray = (int *)malloc(sizeof(int)); // allocate enough memory for 1 fd
			}
			else { // if adding an fd to an existing table
				fdArray = realloc(fdArray, (numberOfFds+1)*sizeof(int)); // resize to fit exactly one more fd
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
				if (fileFd==-1) {
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
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
				if (fileFd==-1) {
					fputs("Could not open file",stderr);
					printf(" %s\n",fileName);
				}
				fdArray[numberOfFds] = fileFd; // add this fd to end fdArray
				numberOfFds++;

				break;
			}
			case 3: // --command
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

				///// SUBPROCESS /////
				pid_t forkValue = fork();
				pid_t wait;

				if (forkValue < 0) {
					fputs("Could not fork child process\n",stderr);
					exit(0);
				}
				else if (forkValue == 0){ // child process
					if (fdArray[atoi(argv[optind])] <=0 ) // check cmd's stdin
						fputs("Error reading input fd\n",stderr);
					if (fdArray[atoi(argv[optind+1])] <= 0 ) // check cmd's stdout
						fputs("Error reading output fd\n",stderr);
					if (fdArray[atoi(argv[optind+2])] <= 0 ) // check cmd's stderr
						fputs("Error reading error fd\n",stderr);
					
					dup2(fdArray[atoi(argv[optind])],0); // STDIN
					close(fdArray[atoi(argv[optind])]);
					dup2(fdArray[atoi(argv[optind+1])],1); // STDOUT
					close(fdArray[atoi(argv[optind+1])]);
					dup2(fdArray[atoi(argv[optind+2])],6); // STDERR
					close(fdArray[atoi(argv[optind+2])]);
					execvp(arg[0],arg);
					fprintf(stderr, "Could not execute command %s\n",argv[optind+3]);
					exit(1);
				}
				else if (forkValue > 0) // parent process
				{
					do{
						wait = waitpid(forkValue, &returnStatus,0);
						if (wait==-1) { fputs("Waitpid error\n",stderr); }
						/* Relevant for later parts of Lab 1
						if (WIFEXITED(returnStatus)) {
			                printf("exited, status=%d\n", WEXITSTATUS(returnStatus));
			            } else if (WIFSIGNALED(returnStatus)) {
			                printf("killed by signal %d\n", WTERMSIG(returnStatus));
			            } else if (WIFSTOPPED(returnStatus)) {
			                printf("stopped by signal %d\n", WSTOPSIG(returnStatus));
			            } else if (WIFCONTINUED(returnStatus)) {
			                printf("continued\n");
			            }
			            */
			        } while (!WIFEXITED(returnStatus)&&!WIFSIGNALED(returnStatus));
				}
				break;
			}
			case 4: // verbose
			{
				if (verbose) // if verbose was already set
					fputs("--verbose\n",stdout);
				else
					verbose=1;
				break;
			}
			default:
				break;
		}
	}
	free(fdArray); // clear any dynamically allocated array
	return 0;
}
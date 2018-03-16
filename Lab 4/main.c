/* 
CS 111
Jonathan Woong
804205763
W16 - Lab 4
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
#include <pthread.h>
#include <time.h>
#include <string.h>

///// DEFINITIONS /////
#define THREADS 100
#define ITERATIONS 200
#define YIELD 300
#define SYNC 500
#define BILLION 1000000000

///// VARIABLES/FLAGS /////
unsigned int numberOfThreads=1; // default=1
unsigned int numberOfIterations=1; // default=1
unsigned int numberOfOps=0;
unsigned int timePerOp=0;
unsigned int errorEncountered=0; // 0 = no, 1 = yes
long long counter=0;
unsigned int opt_yield=0;
unsigned int syncFlag=0;
unsigned int mutexFlag=0;
unsigned int spinFlag=0;
unsigned int atomicFlag=0;
pthread_mutex_t threadMutex;
unsigned int spinLock=0;

///// ROUTINES /////
void add(long long *pointer, long long value) {
        long long sum = *pointer + value;
        if (opt_yield) {
            pthread_yield();
        }
        *pointer = sum;
}

void *threadAdd(void *threadPtr) {
	for (int i=0; i<numberOfIterations; i++) {
		add(&counter,1);
	}
	for (int i=0; i<numberOfIterations; i++) {
		add(&counter,-1);
	}
	pthread_exit(NULL);
}

void *mutexAdd(void *threadPtr) {
	pthread_mutex_lock(&threadMutex);
	for (int i=0; i<numberOfIterations; i++) {
		add(&counter,1);
	}
	for (int i=0; i<numberOfIterations; i++) {
		add(&counter,-1);
	}
	pthread_mutex_unlock(&threadMutex);
	pthread_exit(NULL);
}

void *spinAdd(void *threadPtr) {
	while(__sync_lock_test_and_set(&spinLock,1));
	for (int i=0; i<numberOfIterations; i++) {
		add(&counter,1);
	}
	for (int i=0; i<numberOfIterations; i++) {
		add(&counter,-1);
	}
	__sync_lock_release(&spinLock);
}

void *atomicAdd(void *threadPtr) {
	for (int i=0; i<numberOfIterations; i++) {
		long long oldval=counter;
		__sync_val_compare_and_swap(&counter,oldval,counter++);
	}
	for (int i=0; i<numberOfIterations; i++) {
		long long oldval=counter;
		__sync_val_compare_and_swap(&counter,oldval,counter--);
	}
}

///// MAIN ROUTINE /////
int main(int argc, char *argv[]) {
	///// VARIABLES /////
	int optionIndex=0;
	unsigned int getoptValue=0;
	unsigned int parametersAcquired=0; // 1 for iterations, 1 for threads
	long long timeDifference=0;
	struct timespec start,end;

	///// PARSE PARAMETERS /////
	while(parametersAcquired < 2){
		///// OPTIONS /////
		struct option long_options[] =
		{
			///// PARAMETERS /////
			{"threads", required_argument, 0, THREADS},
			{"iterations", required_argument, 0, ITERATIONS},
			{"yield", required_argument, 0, YIELD},
			{"sync", required_argument, 0, SYNC},
			{0,0,0,0}
		};
		getoptValue = getopt_long(argc,argv,"",long_options,&optionIndex);
		if (getoptValue == -1) {
			break;
		}

		///// SET THREAD/ITERATION COUNT /////
		switch(getoptValue) {
			case 0: break;
			case SYNC: {
				syncFlag=1; // set sync flag
				if (!strncmp(optarg,"m",0)){ // if sync=m
					mutexFlag=1;
				}
				else if (!strncmp(optarg,"s",0)) { // if sync=s
					spinFlag=1;
				}
				else if (!strncmp(optarg,"c",0)) { // if sync=c
				 	atomicFlag=1;
				}
			}
			case YIELD: {
				opt_yield=1;
				break;
			}
			case THREADS: {
				numberOfThreads = atoi(optarg);
				parametersAcquired++;
				break;
			}
			case ITERATIONS: {
				numberOfIterations = atoi(optarg);
				parametersAcquired++;
				break;
			}
			default: break;
		}
	}

	///// PRINT INFORMATION /////
	numberOfOps = (numberOfThreads*numberOfIterations*2);
	fprintf(stdout, "%d threads x %d iterations x (add + subtract) = %d operations\n", numberOfThreads, numberOfIterations, numberOfOps);

	///// MUTEX /////
	if (mutexFlag) {
		pthread_mutex_init(&threadMutex,NULL);
	}

	///// THREADS /////
	clock_gettime(CLOCK_MONOTONIC, &start); // start timer
	pthread_t threadArray[numberOfThreads];
	int createThreads = 0;

	///// MUTEX /////
	if (mutexFlag) {
		for (int i=0; i<numberOfThreads; i++) {
			createThreads = pthread_create(&threadArray[i],NULL,mutexAdd,NULL);
			///// ERROR CHECKING /////
			if (createThreads < 0) {
				fprintf(stderr, "Thread creation error\n");
				errorEncountered++;
			}
		}
	}
	///// SPINLOCK /////
	else if (spinFlag) {
			for (int i=0; i<numberOfThreads; i++) {
			createThreads = pthread_create(&threadArray[i],NULL,spinAdd,NULL);
			///// ERROR CHECKING /////
			if (createThreads < 0) {
				fprintf(stderr, "Thread creation error\n");
				errorEncountered++;
			}
		}	
	}
	///// ATOMIC /////
	else if (atomicFlag) {
		for (int i=0; i<numberOfThreads; i++) {
			createThreads = pthread_create(&threadArray[i],NULL,atomicAdd,NULL);
			///// ERROR CHECKING /////
			if (createThreads < 0) {
				fprintf(stderr, "Thread creation error\n");
				errorEncountered++;
			}
		}
	}
	///// UNPROTECTED /////
	else {
		for (int i=0; i<numberOfThreads; i++) {
			createThreads = pthread_create(&threadArray[i],NULL,threadAdd,NULL);
			///// ERROR CHECKING /////
			if (createThreads < 0) {
				fprintf(stderr, "Thread creation error\n");
				errorEncountered++;
			}
		}
	}
	
	///// JOIN THREADS /////
	for (int i=0; i<numberOfThreads; i++) {
		pthread_join(threadArray[i],NULL);
	}
	///// MUTEX /////
	if (mutexFlag) {
		pthread_mutex_destroy(&threadMutex);
	}
	clock_gettime(CLOCK_MONOTONIC, &end); // end timer

	///// COUNTER CHECKING /////
	if (counter!=0) {
		fprintf(stderr,"ERROR: final count = %lld\n", counter);
		errorEncountered++;
	}

	///// PRINT TIME INFO /////
	timeDifference = (BILLION * (end.tv_sec - start.tv_sec)) + (end.tv_nsec - start.tv_nsec);
	timePerOp = timeDifference/numberOfOps;
	fprintf(stdout, "elapsed time: %lld ns\n", timeDifference);
	fprintf(stdout, "per operation: %u ns\n", timePerOp);

	///// RETURN //////
	if(errorEncountered) {
		exit(-1);
	}
	else {
		exit(0);
	}
	
}
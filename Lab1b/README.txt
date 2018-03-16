Jonathan Woong
804205763
CS 111
Lab 1b

NO TEAM MEMBERS (INDIVIDUAL WORK)

Note to grader: 
	I had an error in Lab 1a where I did dup2(fd[],6) instead of dup2(fd[],2) for the case STDERR. I did not discover my mistake until a week after the due date (I mixed up real fd and index fd from lab spec). 
	I also did not exit simpsh properly in Lab 1a. I thought that if no subprocess is waited on, we cannot check the exit status of the children, so we should just return 0 (since we did not implement --wait yet). 
	Also, no one wants to be my lab partner ): 
	Please be kind with grading my individual work <3

Subcommand algorithms:
	--rdonly, --wronly, --rdwr:
		1. Open file (with flags)
		2. Check for file opening error + check if user attempts to open a file that was closed with --close 
		3. Update fd table

	--pipe
		1. Call pipe() and check for errors
		2. Assign read end and write end to fd table

	--command
		1. Count # of args that come after --command ("--command 0 1 2 cat A-Z a-z" sets argCounter to 6)
		2. Create cmd buffer (contains [cat,A-Z,a-z,NULL])
		3. Check fd's "0 1 2" for error + check if attempting to reuse fd that was closed with --close
		4. Fork()
			- Child does dup2() and closes all fds opened by parent + execute subcommand
			- Parent tracks child process by updating childrenArray + closes pipe ends/fds

	--wait
		1. Close all fds
		2. Reap all children + output child exit status + set program exit status

	--close
		1. Close fd
		2. Track closed fd with closedFdArray

	--abort
		1. Call raise(SIGSEGV)

	--catch
		1. Call signal() with custom signal handler

	--ignore
		1. Call signal() with ignore signal handler

	--default
		1. Call signal() with default signal handler

	--pause
		1. Call pause()

	When no more options specified, free all dynamic arrays and exit().


Limitations:
	Depending on the order of the subcommands and pipes, sometimes the subcommands cannot be executed.
	For example:
		./simpsh --rdonly a --pipe --pipe --wronly b --wronly c --command 0 2 6 sort --command 1 4 6 tr A-Z a-z --command 3 5 6 cat --wait

		In this case, cat will fail. However, this ordering (with the same exact subcommands) will work:
		./simpsh --rdonly a --pipe --pipe --wronly b --wronly c --command 0 2 6 cat --command 1 4 6 sort --command 3 5 6 tr A-Z a-z --wait

	So the subcommands do work, but the order of them matters. This might be because the pipes are closed in one subcommand and are not able to be accessed in later subcommands (race condition).



	
	

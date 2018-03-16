Jonathan Woong
804205763
CS 111
Lab 1a

NO TEAM MEMBERS (INDIVIDUAL WORK)

Limitations:
	For some reason, if I do this:
		./simpsh --rdonly file1 --wronly file2 --wronly file3 --command 0 1 2 sort --command 0 1 2 cat file2 -
	The program will perform the cat command infinitely and create an extremely large file if the process is not killed.

	However, calling cat as the first command will work (even if I call sort as a second command): 
		./simpsh --verbose --rdonly a --wronly b --wronly c --command 0 1 2 cat b - --command 0 1 2 sort

	Also, calling cat without arguments will work just fine (all 3 cases work):
		./simpsh --verbose --rdonly a --wronly b --wronly c --command 0 1 2 cat
		./simpsh --verbose --rdonly a --wronly b --wronly c --command 0 1 2 cat --command 0 1 2 cat
		./simpsh --verbose --rdonly a --wronly b --wronly c --command 0 1 2 sort --command 0 1 2 cat

	The infinite loop must be some type of confusion with redirection.
	

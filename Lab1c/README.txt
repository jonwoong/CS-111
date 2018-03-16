Jonathan Woong
804205763
CS 111
Lab 1c

NO TEAM MEMBERS (INDIVIDUAL WORK)

Note to grader: 
	I had an error in Lab 1a where I did dup2(fd[],6) instead of dup2(fd[],2) for the case STDERR. 
	I did not discover my mistake until a week after the due date (I mixed up real fd and index fd from lab spec). 
	I also did not exit simpsh properly in Lab 1a. 
	I thought that if no subprocess is waited on, we cannot check the exit status of the children, so we should just return 0 (since we did not implement --wait yet). 
	Also, no one wants to be my lab partner ): 
	Please be kind with grading my individual work <3

Profile Benchmarks:
	Scripts:
		1. bashScript.sh: will run all bash benchmarks 5 times and output results to bashBenchmark
		2. simpshScript.sh: will run all simpsh benchmarks 5 times and output results to simpshBenchmark
		3. execlineScript.sh: will run all execline benchmarks 5 times and output results to execlineBenchmark
			execlineScript1.sh: benchmark 1O
			execlineScript2.sh: benchmark 2
			execlineScript3.sh: benchmark 3
		4. dashScript.sh: will run all dash benchmarks 5 times and output results to dashBenchmark
		5. tcshScript.sh: will run all tcsh benchmarks 5 times and output results to tcshBenchmark
		6. testAll.sh: will run all benchmarks above and output results to allResults

		Running ./testAll.sh is equivalent to running all 3 benchmarks on all programs (bash,execline,simpsh,dash,tcsh)

	Setup:
		touch randomFileA randomFileB resultFile1 resultFile2 resultFile3 resultFile4 resultFile5
		base64 /dev/urandom | head -c 10000000 > randomFileA
		base64 /dev/urandom | head -c 10000000 > randomFileB

	BASH
		Benchmark 1:
			$ time cat randomFileA | sort | tr A-Z a-z > resultFile1

			real	0m0.629s
			user	0m0.438s
			sys	0m0.052s

			real	0m0.647s
			user	0m0.444s
			sys	0m0.050s

			real	0m0.697s
			user	0m0.459s
			sys	0m0.046s

			real	0m0.831s
			user	0m0.569s
			sys	0m0.058s

			real	0m0.641s
			user	0m0.435s
			sys	0m0.054s

			Average user time: 0.469s
			Average sys time: 0.052s

		Benchmark 2:
			$ time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && comm resultFile1 resultFile2 > resultFile3

			real	0m0.614s
			user	0m0.425s
			sys	0m0.030s

			real	0m0.591s
			user	0m0.419s
			sys	0m0.035s

			real	0m0.633s
			user	0m0.422s
			sys	0m0.033s

			real	0m0.697s
			user	0m0.421s
			sys	0m0.034s

			real	0m0.597s
			user	0m0.417s
			sys	0m0.036s

			Average user time: 0.4208s
			Average sys time: 0.0336s

		Benchmakrk 3:
			$ time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && wc randomFileA randomFileB > resultFile3

			real	0m0.567s
			user	0m0.414s
			sys	0m0.028s

			real	0m0.562s
			user	0m0.395s
			sys	0m0.030s

			real	0m0.691s
			user	0m0.410s
			sys	0m0.034s

			real	0m0.553s
			user	0m0.394s
			sys	0m0.032s

			real	0m0.620s
			user	0m0.406s
			sys	0m0.036s

			Average user time: 0.4038s
			Average sys time: 0.032s

	SIMPSH
		Benchmark 1:
			$ time ./simpsh --profile --rdonly randomFileA --pipe --pipe --wronly resultFile1 --wronly resultFile2 --command 0 2 6 cat --command 1 4 6 sort --command 3 5 6 tr A-Z a-z --wait 

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.230 seconds to reap in kernelmode
			Children took 0.422084 seconds in usermode
			Children took 0.46206 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.216 seconds to reap in kernelmode
			Children took 0.426340 seconds in usermode
			Children took 0.43756 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.165 seconds to reap in kernelmode
			Children took 0.447845 seconds in usermode
			Children took 0.43194 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.144 seconds to reap in kernelmode
			Children took 0.433968 seconds in usermode
			Children took 0.51549 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.186 seconds to reap in kernelmode
			Children took 0.442537 seconds in usermode
			Children took 0.49168 seconds in kernelmode

			Average user time: 0.4345548s
			Average sys time: 0.65594s

		Benchmark 2:
			$ time ./simpsh --profile --rdonly randomFileA --rdonly randomFileB --pipe --pipe --wronly resultFile1 --wronly resultFile2 --rdwr resultFile3 --rdwr resultFile4 --wronly resultFile5 --command 0 3 7 sort --command 2 8 7 cat --command 1 5 7 sort --command 4 9 7 cat --command 6 10 7 comm resultFile3 resultFile4  --wait

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.0 seconds to reap in kernelmode
			Children took 0.827821 seconds in usermode
			Children took 0.64794 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.0 seconds to reap in kernelmode
			Children took 1.30752 seconds in usermode
			Children took 0.99792 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.268 seconds to reap in kernelmode
			Children took 1.328007 seconds in usermode
			Children took 0.80357 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.0 seconds to reap in kernelmode
			Children took 1.28946 seconds in usermode
			Children took 0.79141 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.353 seconds to reap in kernelmode
			Children took 1.48780 seconds in usermode
			Children took 0.81154 seconds in kernelmode

			Average user time: 1.2481216s
			Average sys time: 0.810476s

		Benchmark 3:
			$ time ./simpsh --profile --rdonly randomFileA --rdonly randomFileB --pipe --pipe --wronly resultFile1 --wronly resultFile2 --wronly resultFile3 --rdonly resultFile4  --wronly resultFile5 --command 0 3 7 sort --command 2 6 7 cat --command 1 5 7 sort --command 4 8 7 cat --command 9 10 7 wc randomFileA randomFileB --wait

			Parent took 0.206 seconds to reap in usermode
			Parent took 0.0 seconds to reap in kernelmode
			Children took 1.400649 seconds in usermode
			Children took 0.82688 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.191 seconds to reap in kernelmode
			Children took 1.182843 seconds in usermode
			Children took 0.59593 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.251 seconds to reap in kernelmode
			Children took 1.165917 seconds in usermode
			Children took 0.68001 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.254 seconds to reap in kernelmode
			Children took 1.256181 seconds in usermode
			Children took 0.75818 seconds in kernelmode

			Parent took 0.0 seconds to reap in usermode
			Parent took 0.314 seconds to reap in kernelmode
			Children took 1.170174 seconds in usermode
			Children took 0.68343 seconds in kernelmode

			Average user time: 1.2763528s
			Average sys time: 0.910886s

	EXECLINE
		Benchmark 1:
			time -p foreground { redirfd -w 1 resultFile1 pipeline { pipeline { cat randomFileA } sort } tr A-Z a-z }

			real 0.74
			user 0.01
			sys 0.01

			real 0.63
			user 0.01
			sys 0.01

			real 0.62
			user 0.01
			sys 0.01

			real 0.64
			user 0.01
			sys 0.01

			real 0.62
			user 0.01
			sys 0.01

			Average user time: 0.01s
			Average sys time: 0.01s

		Benchmark 2:
			time -p foreground { 
				redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
				redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
				redirfd -w 1 resultFile3 foreground { comm resultFile1 resultFile2 } }

			real 1.81
			user 0.20
			sys 0.07

			real 1.83
			user 0.20
			sys 0.07

			real 1.71
			user 0.21
			sys 0.07

			real 1.92
			user 0.21
			sys 0.06

			real 1.74
			user 0.20
			sys 0.07

			Average user time: 0.204s
			Average sys time: 0.068s

		Benchmark 3:
			time -p foreground { 
				redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
				redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
				redirfd -w 1 resultFile3 foreground { wc randomFileA randomFileB } }

			real 1.75
			user 0.35
			sys 0.05

			real 1.55
			user 0.35
			sys 0.05

			real 1.72
			user 0.35
			sys 0.04

			real 1.51
			user 0.33
			sys 0.06

			real 1.50
			user 0.35
			sys 0.04

			Average user time: 0.346s
			Average sys time: 0.048s

	DASH
		Benchmark 1:
			$ time cat randomFileA | sort | tr A-Z a-z > resultFile1

			real	0m0.594s
			user	0m0.424s
			sys	0m0.052s

			real	0m0.614s
			user	0m0.446s
			sys	0m0.045s

			real	0m0.615s
			user	0m0.437s
			sys	0m0.054s

			real	0m0.600s
			user	0m0.433s
			sys	0m0.055s

			real	0m0.661s
			user	0m0.430s
			sys	0m0.055s

			Average user time: 0.434s
			Average sys time: 0.0522s

		Benchmark 2:
			$ time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && comm resultFile1 resultFile2 > resultFile3

			real	0m0.578s
			user	0m0.393s
			sys	0m0.032s

			real	0m0.858s
			user	0m0.408s
			sys	0m0.042s

			real	0m0.561s
			user	0m0.409s
			sys	0m0.033s

			real	0m0.567s
			user	0m0.408s
			sys	0m0.034s

			real	0m0.576s
			user	0m0.395s
			sys	0m0.030s

			Average user time: 0.4026s
			Average sys time: 0.0342s

		Benchmark 3:
			$ time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && wc randomFileA randomFileB > resultFile3

			real	0m0.569s
			user	0m0.406s
			sys	0m0.038s

			real	0m0.660s
			user	0m0.410s
			sys	0m0.032s

			real	0m0.562s
			user	0m0.398s
			sys	0m0.029s

			real	0m0.567s
			user	0m0.405s
			sys	0m0.037s

			real	0m1.080s
			user	0m0.399s
			sys	0m0.038s

			Average user time: 0.4036s
			Average sys time: 0.0348s

	TCSH
		Benchmark 1:
			$ /usr/bin/time -p cat randomFileA | sort | tr A-Z a-z > resultFile1

			real 0.27
			user 0.00
			sys 0.00

			real 0.27
			user 0.00
			sys 0.00

			real 0.27
			user 0.00
			sys 0.00

			real 0.26
			user 0.00
			sys 0.00

			real 0.29
			user 0.00
			sys 0.00

			Average user time: 0.00s
			Average sys time: 0.00s

		Benchmark 2:
			$ /usr/bin/time -p sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && comm resultFile1 resultFile2 > resultFile3

			real 0.44
			user 0.41
			sys 0.01

			real 0.42
			user 0.40
			sys 0.01

			real 0.42
			user 0.40
			sys 0.01

			real 0.42
			user 0.39
			sys 0.01

			real 0.42
			user 0.41
			sys 0.00

			Average user time: 0.402s
			Average sys time: 0.008s

		Benchmark 3:
			$ /usr/bin/time -p sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && wc randomFileA randomFileB > resultFile3

			real 0.42
			user 0.40
			sys 0.01

			real 0.44
			user 0.40
			sys 0.01

			real 0.41
			user 0.39
			sys 0.00

			real 0.43
			user 0.40
			sys 0.01

			real 0.43
			user 0.40
			sys 0.01

			Average user time: 0.398s
			Average sys time: 0.01s




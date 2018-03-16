#!/usr/local/cs/execline-2.1.4.5/bin/execlineb

foreground { printf "EXECLINE: Running benchmark 2\n" }

redirfd -a 1 execlineBenchmark foreground { printf "EXECLINE Benchmark 2:\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { comm resultFile1 resultFile2 } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { comm resultFile1 resultFile2 } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { comm resultFile1 resultFile2 } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { comm resultFile1 resultFile2 } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { comm resultFile1 resultFile2 } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }

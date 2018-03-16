#!/usr/local/cs/execline-2.1.4.5/bin/execlineb

foreground { printf "EXECLINE: Running benchmark 3\n" }

redirfd -a 1 execlineBenchmark foreground { printf "EXECLINE Benchmark 3:\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { wc randomFileA randomFileB } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { wc randomFileA randomFileB } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { wc randomFileA randomFileB } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { wc randomFileA randomFileB } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
redirfd -a 2 execlineBenchmark foreground { time -p foreground { 
	redirfd -w 1 resultFile1 foreground { pipeline { sort randomFileA } cat } 
	redirfd -w 1 resultFile2 foreground { pipeline { sort randomFileB } cat }
	redirfd -w 1 resultFile3 foreground { wc randomFileA randomFileB } } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 

foreground { rm randomFileA randomFileB }
foreground { rm resultFile1 resultFile2 resultFile3 }
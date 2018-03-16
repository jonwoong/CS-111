#!/usr/local/cs/execline-2.1.4.5/bin/execlineb

foreground { printf "EXECLINE: Running benchmark 1\n" }
foreground { touch randomFileA randomFileB }
foreground { touch resultFile1 resultFile2 resultFile3 }
foreground { touch execlineBenchmark }
redirfd -w 1 randomFileA foreground { pipeline { base64 /dev/urandom } head -c 10000000 }
redirfd -w 1 randomFileB foreground { pipeline { base64 /dev/urandom } head -c 10000000 }

redirfd -a 1 execlineBenchmark foreground { printf "EXECLINE Benchmark 1:\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { redirfd -w 1 resultFile1 pipeline { pipeline { cat randomFileA } sort } tr A-Z a-z } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { redirfd -w 1 resultFile1 pipeline { pipeline { cat randomFileA } sort } tr A-Z a-z } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
redirfd -a 2 execlineBenchmark foreground { time -p foreground { redirfd -w 1 resultFile1 pipeline { pipeline { cat randomFileA } sort } tr A-Z a-z } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { redirfd -w 1 resultFile1 pipeline { pipeline { cat randomFileA } sort } tr A-Z a-z } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" }
redirfd -a 2 execlineBenchmark foreground { time -p foreground { redirfd -w 1 resultFile1 pipeline { pipeline { cat randomFileA } sort } tr A-Z a-z } }
redirfd -a 1 execlineBenchmark foreground { printf "\n" } 
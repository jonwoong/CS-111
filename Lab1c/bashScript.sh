#!/bin/bash

touch randomFileA randomFileB 
touch resultFile1 resultFile2 resultFile3
touch bashBenchmark
base64 /dev/urandom | head -c 10000000 > randomFileA
base64 /dev/urandom | head -c 10000000 > randomFileB

printf "BASH: Running benchmark 1\n"
printf "BASH Benchmark 1:\n" >> bashBenchmark
for var in 0 1 2 3 4
do
(time cat randomFileA | sort | tr A-Z a-z > resultFile1) &>> bashBenchmark
done
printf "\n" >> bashBenchmark

printf "BASH: Running benchmark 2\n"
printf "BASH Benchmark 2:\n" >> bashBenchmark
for var in 0 1 2 3 4
do
(time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && comm resultFile1 resultFile2 > resultFile3) &>> bashBenchmark
done
printf "\n" >> bashBenchmark

printf "BASH: Running benchmark 3\n"
printf "BASH Benchmark 3:\n" >> bashBenchmark
for var in 0 1 2 3 4
do
(time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && wc randomFileA randomFileB > resultFile3) &>> bashBenchmark
done
printf "\n" >> bashBenchmark

rm randomFileA randomFileB
rm resultFile1 resultFile2 resultFile3



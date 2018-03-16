#!/bin/bash

touch randomFileA randomFileB 
touch resultFile1 resultFile2 resultFile3 resultFile4 resultFile5
touch simpshBenchmark
base64 /dev/urandom | head -c 10000000 > randomFileA
base64 /dev/urandom | head -c 10000000 > randomFileB

printf "SIMPSH: Running benchmark 1\n"
printf "SIMPSH: Benchmark 1:\n" >> simpshBenchmark
for var in 0 1 2 3 4
do
(./simpsh --profile --rdonly randomFileA --pipe --pipe --wronly resultFile1 --wronly resultFile2 --command 0 2 6 cat --command 1 4 6 sort --command 3 5 6 tr A-Z a-z --wait) &>> simpshBenchmark
done
printf "\n" >> simpshBenchmark

printf "SIMPSH: Running benchmark 2\n"
printf "SIMPSH: Benchmark 2:\n" >> simpshBenchmark
for var in 0 1 2 3 4
do
(./simpsh --profile --rdonly randomFileA --rdonly randomFileB --pipe --pipe --wronly resultFile1 --wronly resultFile2 --rdwr resultFile3 --rdwr resultFile4 --wronly resultFile5 --command 0 3 7 sort --command 2 8 7 cat --command 1 5 7 sort --command 4 9 7 cat --command 6 10 7 comm resultFile3 resultFile4  --wait) &>> simpshBenchmark
done
printf "\n" >> simpshBenchmark

printf "SIMPSH: Running benchmark 3\n"
printf "SIMPSH: Benchmark 3:\n" >> simpshBenchmark
for var in 0 1 2 3 4
do
(./simpsh --profile --rdonly randomFileA --rdonly randomFileB --pipe --pipe --wronly resultFile1 --wronly resultFile2 --wronly resultFile3 --rdonly resultFile4  --wronly resultFile5 --command 0 3 7 sort --command 2 6 7 cat --command 1 5 7 sort --command 4 8 7 cat --command 9 10 7 wc randomFileA randomFileB --wait) &>> simpshBenchmark
done
printf "\n" >> simpshBenchmark

rm randomFileA randomFileB
rm resultFile1 resultFile2 resultFile3 resultFile4 resultFile5
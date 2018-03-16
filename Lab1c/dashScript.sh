#!/bin/sh

touch randomFileA randomFileB 
touch resultFile1 resultFile2 resultFile3
touch dashBenchmark
base64 /dev/urandom | head -c 10000000 > randomFileA
base64 /dev/urandom | head -c 10000000 > randomFileB

printf "DASH: Running benchmark 1\n"
printf "DASH Benchmark 1:\n" >> dashBenchmark
for var in 0 1 2 3 4
do
(time cat randomFileA | sort | tr A-Z a-z > resultFile1) &>> dashBenchmark
done
printf "\n" >> dashBenchmark

printf "DASH: Running benchmark 2\n"
printf "DASH: Benchmark 2:\n" >> dashBenchmark
for var in 0 1 2 3 4
do
(time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && comm resultFile1 resultFile2 > resultFile3) &>> dashBenchmark
done
printf "\n" >> dashBenchmark

printf "DASH: Running benchmark 3\n"
printf "DASH: Benchmark 3:\n" >> dashBenchmark
for var in 0 1 2 3 4
do
(time sort randomFileA | cat > resultFile1 && sort randomFileB | cat > resultFile2 && wc randomFileA randomFileB > resultFile3) &>> dashBenchmark
done
printf "\n" >> dashBenchmark

rm randomFileA randomFileB
rm resultFile1 resultFile2 resultFile3



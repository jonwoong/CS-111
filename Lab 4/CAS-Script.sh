#!/bin/bash

touch CASNY-Results
touch CASY-Results

printf "=====CAS NON-YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=1 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=1 --iterations=100 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=1 --iterations=1000 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=1 --iterations=10000 &>> CASNY-Results
done
printf "\n\n" >> CASNY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=2 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=2 --iterations=100 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=2 --iterations=1000 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=2 --iterations=10000 &>> CASNY-Results
done
printf "\n\n" >> CASNY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=4 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=4 --iterations=100 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=4 --iterations=1000 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=4 --iterations=10000 &>> CASNY-Results
done
printf "\n\n" >> CASNY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=10 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=10 --iterations=100 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=10 --iterations=1000 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=10 --iterations=10000 &>> CASNY-Results
done
printf "\n\n" >> CASNY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=50 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=50 --iterations=100 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=50 --iterations=1000 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=50 --iterations=10000 &>> CASNY-Results
done
printf "\n\n" >> CASNY-Results

printf "100 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=90 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=90 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=90 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=90 --iterations=10 &>> CASNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --threads=90 --iterations=10 &>> CASNY-Results
done
printf "\n\n" >> CASNY-Results

printf "=====CAS YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=1 --iterations=10 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=1 --iterations=100 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=1 --iterations=1000 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=1 --iterations=10000 &>> CASY-Results
done
printf "\n\n" >> CASY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=2 --iterations=10 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=2 --iterations=100 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=2 --iterations=1000 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=2 --iterations=10000 &>> CASY-Results
done
printf "\n\n" >> CASY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=4 --iterations=10 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=4 --iterations=100 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=4 --iterations=1000 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=4 --iterations=10000 &>> CASY-Results
done
printf "\n\n" >> CASY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=10 --iterations=10 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=10 --iterations=100 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=10 --iterations=1000 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=10 --iterations=10000 &>> CASY-Results
done
printf "\n\n" >> CASY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=50 --iterations=10 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=50 --iterations=100 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=50 --iterations=1000 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=50 --iterations=10000 &>> CASY-Results
done
printf "\n\n" >> CASY-Results

printf "90 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=90 --iterations=10 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=90 --iterations=100 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=90 --iterations=1000 &>> CASY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=c --yield=1 --threads=90 --iterations=10000 &>> CASY-Results
done
printf "\n\n" >> CASY-Results
#!/bin/bash

touch SNY-Results
touch SY-Results

printf "=====SPIN NON-YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=1 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=1 --iterations=100 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=1 --iterations=1000 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=1 --iterations=10000 &>> SNY-Results
done
printf "\n\n" >> SNY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=2 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=2 --iterations=100 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=2 --iterations=1000 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=2 --iterations=10000 &>> SNY-Results
done
printf "\n\n" >> SNY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=4 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=4 --iterations=100 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=4 --iterations=1000 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=4 --iterations=10000 &>> SNY-Results
done
printf "\n\n" >> SNY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=10 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=10 --iterations=100 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=10 --iterations=1000 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=10 --iterations=10000 &>> SNY-Results
done
printf "\n\n" >> SNY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=50 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=50 --iterations=100 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=50 --iterations=1000 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=50 --iterations=10000 &>> SNY-Results
done
printf "\n\n" >> SNY-Results

printf "100 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=90 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=90 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=90 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=90 --iterations=10 &>> SNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --threads=90 --iterations=10 &>> SNY-Results
done
printf "\n\n" >> SNY-Results

printf "=====SPIN YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=1 --iterations=10 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=1 --iterations=100 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=1 --iterations=1000 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=1 --iterations=10000 &>> SY-Results
done
printf "\n\n" >> SY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=2 --iterations=10 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=2 --iterations=100 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=2 --iterations=1000 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=2 --iterations=10000 &>> SY-Results
done
printf "\n\n" >> SY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=4 --iterations=10 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=4 --iterations=100 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=4 --iterations=1000 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=4 --iterations=10000 &>> SY-Results
done
printf "\n\n" >> SY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=10 --iterations=10 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=10 --iterations=100 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=10 --iterations=1000 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=10 --iterations=10000 &>> SY-Results
done
printf "\n\n" >> SY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=50 --iterations=10 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=50 --iterations=100 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=50 --iterations=1000 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=50 --iterations=10000 &>> SY-Results
done
printf "\n\n" >> SY-Results

printf "90 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=90 --iterations=10 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=90 --iterations=100 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=90 --iterations=1000 &>> SY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=s --yield=1 --threads=90 --iterations=10000 &>> SY-Results
done
printf "\n\n" >> SY-Results
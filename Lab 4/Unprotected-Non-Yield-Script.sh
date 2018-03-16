#!/bin/bash

touch UNY-Results

printf "=====UNPROTECTED NON-YIELD=====\n"
printf "1 thread && 10 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=10 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 20 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=20 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 30 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=30 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 40 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=40 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 50 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=50 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 60 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=60 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 70 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=70 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 80 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=80 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 90 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=90 &>> UNY-Results
done
printf "\n\n" >> UNY-Results

printf "1 thread && 100 iterations\n"
for var in 0 1 2 3 4
do
./addtest --threads=1 --iterations=100 &>> UNY-Results
done
printf "\n\n" >> UNY-Results


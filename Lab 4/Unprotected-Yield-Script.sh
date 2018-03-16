#!/bin/bash

touch UY-Results

printf "=====UNPROTECTED YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=1 --iterations=10 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=1 --iterations=100 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=1 --iterations=1000 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=1 --iterations=10000 &>> UY-Results
done
printf "\n\n" >> UY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=2 --iterations=10 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=2 --iterations=100 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=2 --iterations=1000 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=2 --iterations=10000 &>> UY-Results
done
printf "\n\n" >> UY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=4 --iterations=10 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=4 --iterations=100 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=4 --iterations=1000 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=4 --iterations=10000 &>> UY-Results
done
printf "\n\n" >> UY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=10 --iterations=10 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=10 --iterations=100 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=10 --iterations=1000 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=10 --iterations=10000 &>> UY-Results
done
printf "\n\n" >> UY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=50 --iterations=10 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=50 --iterations=100 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=50 --iterations=1000 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=50 --iterations=10000 &>> UY-Results
done
printf "\n\n" >> UY-Results

printf "90 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=90 --iterations=10 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=90 --iterations=100 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=90 --iterations=1000 &>> UY-Results
done
for var in 0 1 2 3 4
do
./addtest --yield=1 --threads=90 --iterations=10000 &>> UY-Results
done
printf "\n\n" >> UY-Results
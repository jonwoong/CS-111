#!/bin/bash

touch MNY-Results
touch MY-Results

printf "=====MUTEX NON-YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=1 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=1 --iterations=100 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=1 --iterations=1000 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=1 --iterations=10000 &>> MNY-Results
done
printf "\n\n" >> MNY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=2 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=2 --iterations=100 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=2 --iterations=1000 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=2 --iterations=10000 &>> MNY-Results
done
printf "\n\n" >> MNY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=4 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=4 --iterations=100 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=4 --iterations=1000 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=4 --iterations=10000 &>> MNY-Results
done
printf "\n\n" >> MNY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=10 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=10 --iterations=100 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=10 --iterations=1000 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=10 --iterations=10000 &>> MNY-Results
done
printf "\n\n" >> MNY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=50 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=50 --iterations=100 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=50 --iterations=1000 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=50 --iterations=10000 &>> MNY-Results
done
printf "\n\n" >> MNY-Results

printf "100 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=90 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=90 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=90 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=90 --iterations=10 &>> MNY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --threads=90 --iterations=10 &>> MNY-Results
done
printf "\n\n" >> MNY-Results

printf "=====MUTEX YIELD=====\n"
printf "1 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=1 --iterations=10 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=1 --iterations=100 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=1 --iterations=1000 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=1 --iterations=10000 &>> MY-Results
done
printf "\n\n" >> MY-Results

printf "2 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=2 --iterations=10 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=2 --iterations=100 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=2 --iterations=1000 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=2 --iterations=10000 &>> MY-Results
done
printf "\n\n" >> MY-Results

printf "4 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=4 --iterations=10 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=4 --iterations=100 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=4 --iterations=1000 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=4 --iterations=10000 &>> MY-Results
done
printf "\n\n" >> MY-Results

printf "10 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=10 --iterations=10 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=10 --iterations=100 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=10 --iterations=1000 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=10 --iterations=10000 &>> MY-Results
done
printf "\n\n" >> MY-Results

printf "50 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=50 --iterations=10 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=50 --iterations=100 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=50 --iterations=1000 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=50 --iterations=10000 &>> MY-Results
done
printf "\n\n" >> MY-Results

printf "90 thread && 10-10000 iterations\n"
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=90 --iterations=10 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=90 --iterations=100 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=90 --iterations=1000 &>> MY-Results
done
for var in 0 1 2 3 4
do
./addtest --sync=m --yield=1 --threads=90 --iterations=10000 &>> MY-Results
done
printf "\n\n" >> MY-Results
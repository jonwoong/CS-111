#!/bin/bash

./Unprotected-Non-Yield-Script.sh
sleep 3
./Unprotected-Yield-Script.sh
sleep 3
./Mutex-Script.sh
sleep 3
./Spin-Script.sh
sleep 3
./CAS-Script.sh
sleep 3

printf "\n=====ALL SCRIPTS COMPLETED=====\n"


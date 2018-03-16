CC=gcc
CFLAGS=-Wall
LDFLAGS=-lrt

all:
	chmod 777 runAllScripts.sh Unprotected-Yield-Script.sh Unprotected-Non-Yield-Script.sh Mutex-Script.sh Spin-Script.sh CAS-Script.sh
	cp main.c addtest.c
	gcc -g -O -c -std=c11 addtest.c
	gcc addtest.o -lrt -o addtest 

clean:
	rm -f addtest addtest.o addtest.c *Results

dist:
	tar -czf lab4-Woong.tar.gz main.c Makefile Unprotected-Non-Yield-Script.sh Unprotected-Yield-Script.sh CAS-Script.sh Mutex-Script.sh Spin-Script.sh  runAllScripts.sh answers.txt graphs.pdf

check: runAllScripts.sh
	./runAllScripts.sh

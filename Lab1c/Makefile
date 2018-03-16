CC=gcc 
CFLAGS=-Wall

simpsh: simpsh.o
	gcc simpsh.o -o simpsh
simpsh.o: simpsh.c
	gcc -g -O -c -std=c11 simpsh.c
simpsh.c: main.c
	cp main.c simpsh.c

clean:
	rm -f simpsh simpsh.o simpsh.c

dist:
	tar -czf lab1-Woong.tar.gz main.c Makefile test.sh README.txt bashScript.sh simpshScript.sh execlineScript.sh execlineScript1.sh execlineScript2.sh execlineScript3.sh dashScript.sh tcshScript.sh testAll.sh results.pdf

check: test.sh
	./test.sh

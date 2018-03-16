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
	tar -czf lab1-Woong.tar.gz main.c Makefile test.sh README.txt

check: test.sh
	./test.sh

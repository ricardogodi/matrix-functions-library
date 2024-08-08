# Makefile for Matrix Functions Library

all: program

program: main.o
	gcc -Wall -g -o program main.o

main.o: main.c prog2.h
	gcc -Wall -g -c main.c

clean:
	rm -f program *.o

.PHONY: all clean

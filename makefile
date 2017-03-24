CC = gcc
FLAGS = -ansi -Wall -g -Iinclude
all: assignment

assignment:
	gcc db.c -o db.o -c
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
	rm db.o

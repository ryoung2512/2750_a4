CC = gcc
FLAGS = -ansi -Wall -g -Iinclude
all: assignment

assignment:
	# compiles the database
	$(CC) db.c -o db.o -c
	$(CC) db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
	rm db.o
	# compiles a1 and makes the c file for post.cc
	$(CC) a1/a1.c a1/list.c a1/utils.c $(FLAGS) -o a1/a1_converter
	./a1/a1_converter a2/post.cc
	# creates the library
	cd a2 && $(CC) -c stream.c $(FLAGS) -o stream.o \
	&& ar cr libstream.a stream.o \
	&& $(CC) post.c $(FLAGS) -o post.o -c \
	&& $(CC) post.o -o post -L. -lstream \
	&& $(CC) addauthor.c $(FLAGS) -o addauthor.o -c \
	&& $(CC) addauthor.o -o addauthor -L. -lstream
	# creates the parser
	$(CC) parser.c commands.c $(FLAGS) -o parser
	rm a2/*.o

clean:
	rm *.o

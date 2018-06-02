CC=cc
CFLAGS=-Wall -Wpedantic -std=c99 -g -I../include -DDZF_DEBUG
LIBS=

all: main

main: 
		${CC} ${CFLAGS} -o $@ $@.c ${LIBS}

memcheck:
		valgrind --tool=memcheck --leak-check=full -v ./main

gcc:
		gcc ${CFLAGS} -o main main.c ${LIBS}

clang:
		clang ${CFLAGS} -o main main.c ${LIBS}

clean:
		rm -f main ${LIBS} vgcore.* core.*

FLAGS = -Wall -std=gnu99

all: shvec.out shvalloc.out regexlib.out

shvec.out: shvec.c shvalloc.h shvec.h shvalloc.c
	gcc $(FLAGS) shvalloc.c shvec.c -o shvec.out

shvalloc.out: shvalloc.h shvalloc.c
	gcc $(FLAGS) shvalloc.c -o shvalloc.out

shchgrp.out: shvec.c shvec.h regexlib.h regexlib.c shchgrp.c
	gcc $(FLAGS) regexlib.c shchgrp.c shvec.c shvalloc.c -o shchgrp.out

regexlib.out: regexlib.c regexlib.h
	gxx $(FLAGS) regexlib.c -o regexlib.o

test: 
	make -s test_real

test_real: test_shvalloc test_shvec
	make clean; echo "Tests done"

test_shvalloc: test_shvalloc.out
	./test_shvalloc.out

test_shvec: test_shvec.out
	./test_shvec.out

clean:
	-rm *.out $(objects)

test_shvalloc.out: shvalloc.h minunit.h shvalloc.c test_shvalloc.c 
	gcc -g $(FLAGS) shvalloc.c test_shvalloc.c -o test_shvalloc.out

test_shvec.out: minunit.h shvec.c shvec.h test_shvec.c
	gcc -g $(FLAGS) shvalloc.c test_shvec.c -o test_shvec.out

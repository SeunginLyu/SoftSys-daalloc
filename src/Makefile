FLAGS = -Wall

all: shvec.out shvalloc.out

shvec.out: shvec.c shvec.h
	gcc $(FLAGS) shvec.c -o shvec.out

shvalloc.out: shvalloc.h shvalloc.c
	gcc $(FLAGS) shvalloc.c -o shvalloc.out

shchgrp.out: shvec.c shvec.h
	gcc $(FLAGS) shchgrp.c -o shchgrp.out

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
	gcc -g $(FLAGS) test_shvec.c -o test_shvec.out

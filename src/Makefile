FLAGS = -Wall

all: shvec.out

shvec.out: shvec.c shvec.h
	gcc $(FLAGS) shvec.c -o shvec.out

test: test_shvalloc test_shvec
	echo "Tests done"

test_shvalloc: test_shvalloc.out
	./test_shvalloc.out

test_shvec: test_shvec.out
	./test_shvec.out

clean:
	rm shvec.out

test_shvalloc.out: minunit.h test_shvalloc.c 
	gcc -g $(FLAGS) test_shvalloc.c -o test_shvalloc.out

test_shvec.out: minunit.h shvec.c shvec.h test_shvec.c
	gcc -g $(FLAGS) test_shvec.c -o test_shvec.out
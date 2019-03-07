FLAGS = -Wall

all: shvec.out

shvec.out: shvec.c shvec.h
	gcc $(FLAGS) shvec.c -o shvec.out

test: shvec.c shvec.h
	echo "Tests are running!"

clean:
	rm shvec.out

test_shvalloc.out: minunit.h test_shvalloc.c
	gcc -g -Wall test_shvalloc.c -o test_shvalloc.out
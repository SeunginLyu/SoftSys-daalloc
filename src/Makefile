FLAGS = -Wall

all: shvec.out

shvec.out: shvec.c shvec.h
	gcc $(FLAGS) shvec.c -o shvec.out

test: test_shvalloc.out
	echo "Tests are starting..."
	./test_shvalloc.out

clean:
	rm shvec.out

test_shvalloc.out: minunit.h test_shvalloc.c shvec.c shvec.h
	gcc -g $(FLAGS) test_shvalloc.c -o test_shvalloc.out

/*
To run the test, type in your command line 
"make test_shvec && ./test_shvec.out"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "minunit.h"
#include "shvec.h"
#include "shvec.c"

int tests_run = 0;

static char *test_shvec() {
    char *message;
    puts("Testing shvec_create");
    int my_shvec = shvec_create();
    printf("id %d\n", my_shvec);
    message = "    shvec_create should return an int id of 0";
    mu_assert(message, my_shvec == 0);
    puts("    passed\n");

    puts("Testing shvec_set and shvec_get");
    shvec_set(my_shvec, 0, 10);
    int x = shvec_get(my_shvec, 0);
    message = "    shvec_set(my_shvec, 0, 10), shvec_get(my_shvec, 0) should return 10";
    mu_assert(message, x == 10);
    puts("    passed\n");

    printf("Setting [5] to 5\n");
    shvec_set(my_shvec, 5, 5);
    printf("size of shvector %d\n", shvec_get_size(my_shvec));
    printf("value at [4]: %d\n", shvec_get(my_shvec, 4));
    printf("value at [5]: %d\n", shvec_get(my_shvec, 5));

    puts("Testing shvec_set and shvec_get 2");
    shvec_set(my_shvec, 5, 5);
    int a = shvec_get(my_shvec, 4);
    int b = shvec_get(my_shvec, 5);
    int size = shvec_get_size(my_shvec);
    message = "    shvec_set(my_shvec, 5, 5), shvec_get(my_shvec, 4) should return 0";
    mu_assert(message, a == 0);
    message = "    shvec_set(my_shvec, 5, 5), shvec_get(my_shvec, 5) should return 5";
    mu_assert(message, b == 5);
    message = "    shvec_set(my_shvec, 5, 5), shvec_array[my_shvec.size] should return 5";
    mu_assert(message, size == 5);
    puts("    passed\n");

    puts("Testing Resizing");
    shvec_set(my_shvec, 11, 5);
    int s = shvec_get_size(my_shvec);
    int k = shvec_get(my_shvec, 11);
    message = "    shvec_set(my_shvec, 11, 5) shvec_get(my_shvec,11) should return 5";
    mu_assert(message, k == 5);
    message = "    shvec_set(my_shvec, 11, 5) shvec_get(my_shvec,11) should return size of 11";
    mu_assert(message, s == 11);
    puts("    passed\n");

    puts("Checking if shvec is available.");
    message = "    Shvec should be in use.";
    mu_assert(message, shvec_is_available(my_shvec) == 1);
    puts("    passed\n");

    puts("Checking if shvec is available after free.");
    shvec_free(my_shvec);
    message = "    Shvec should be free";
    mu_assert(message, shvec_is_available(my_shvec) == 0);
    puts("    passed\n");
    return NULL;
}

static char * all_tests() {
    mu_run_test(test_shvec);
    return NULL;
}

int main(int argc, char **argv) {
    printf("Running shvec tests:\n");

    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

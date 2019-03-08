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

int tests_run = 0;

static char *test_dummy() {
    char *message = "placeholder text";
    mu_assert(message, 1==1);
    return NULL;
}

static char * all_tests() {
    mu_run_test(test_dummy);
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
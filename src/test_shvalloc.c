/*
To run the test, type in your command line 
"make test_shvalloc && ./test_shvalloc.out" 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "minunit.h"
#include <stdint.h>

int tests_run = 0;

void* shvalloc(size_t size){
    // to be replaced with shvalloc
    void* res = malloc(size);
    return res;
}

static char *test_size_of_allocated_space() {
    int* res = shvalloc(sizeof(int));
    char *message = "Assigned sizeof(int), Expected sizeof(int) did not get sizeof(int)";
    mu_assert(message, sizeof(*res) == sizeof(int));
    return NULL;
}

static char *test_no_duplicate_address() {
    int* a = shvalloc(sizeof(int));
    int* b = shvalloc(sizeof(int));
    char *message = "shvalloc should not allocate the same address twice, Expected a !=b";
    mu_assert(message, a != b);
    return NULL;
}

// assuming 64bit OS, find the stack pointer
uint64_t getsp( void )
{
    uint64_t sp;
    asm( "mov %%rsp, %0" : "=rm" ( sp ));
    return sp;
}
static char *test_address_lower_than_stack_pointer() {
    int* a = shvalloc(sizeof(int));
    uint64_t sp= getsp();
    char *message = "shvalloc should return address lower than that of the stack pointer";
    mu_assert(message, a < (int*)&sp);
    return NULL;
}
static char *test_size_max(){
    int* a = shvalloc(SIZE_MAX);
    char *message = "shvalloc(SIZE_MAX) should return NULL";
    mu_assert(message, a == NULL);
    return NULL;
}
static char *test_size_zero(){
    int* a = shvalloc(0);
    char *message = "shvalloc(0) should return a pointer not NULL and that is subject to free";
    mu_assert(message, a != NULL);
    return NULL;
}

static char * all_tests() {
    mu_run_test(test_size_of_allocated_space);
    mu_run_test(test_no_duplicate_address);
    mu_run_test(test_address_lower_than_stack_pointer);
    mu_run_test(test_size_max);
    mu_run_test(test_size_zero);
    return NULL;
}

int main(int argc, char **argv) {
    printf("Running shvalloc tests:\n");

    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

#include "shvec.h"
#include "shvalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shvec_expand(int id);

typedef struct {
    int size;       // number of initialized values
    int max_size;   // max number of values
    int *data;      // array of values
    //todo: make max_size and size unsigned types.
} Shvector;

Shvector shvec_array[MAX_SHVECS];
int shvec_available[MAX_SHVECS];

/*
 * Initializes a shvec in the shvec_array at id
 */
int shvec_initialize(int id){
    //todo: shvalloc error handling
    // int* data_ptr = shvalloc(sizeof(int)*INIT_SIZE);
    int* data_ptr = malloc(sizeof(int)*INIT_SIZE);
    shvec_array[id] = (Shvector) {.size=0, .max_size=INIT_SIZE, .data=data_ptr};
    shvec_available[id] = 1;
    return id;
}
/*
 * Creates a new Shvec
 * Returns a new Shvec id (Returns -1 on failure)
 */
int shvec_create(){
    int id;
    for(id = 0; id < MAX_SHVECS; id++){
        if (shvec_available[id] == 0){
            return shvec_initialize(id);
        }
    }
    return -1;
}

/*
 * Expand memory allocation of shvec's data.
 */
int shvec_expand(int id) {
    // int* old_data_ptr = shvec_array[id].data;
    // int old_size = shvec_array[id].size;

    // Catch int overflow before changing max_size
    if (shvec_array[id].max_size >= (INT_MAX / GROWTH_FACTOR) \
        || shvec_array[id].max_size < 0) {
        fprintf(stderr, "ERROR: Reached maximum array size. max_size int overflow");
        return 1;
    }

    shvec_array[id].max_size = shvec_array[id].max_size * GROWTH_FACTOR;

    //todo: shvalloc error handling
    shvec_array[id].data = realloc(shvec_array[id].data, sizeof(int)*shvec_array[id].max_size);


    // shvec_array[id].data = shvalloc(sizeof(int)*shvec_array[id].max_size);
    // shvec_array[id].size++;

    // populate new vector
    // for (int i = 0; i < old_size; i++) {
    //     shvec_array[id].data[i] = old_data_ptr[i];
    // }
    // shvec_array[id].data[old_size] = value;

    // shvfree(old_data_ptr);
    return shvec_array[id].data;
}

/*
 * Appends a value to the shvec, reallocates the array if necessary
 */
int shvec_append(int id, int value){
    shvec_array[id].size += 1;

    while(shvec_array[id].size > shvec_array[id].max_size-1){
        int* new_data_arr = shvec_expand(id);
    }

    shvec_array[id].data[shvec_array[id].size] = value;
    return 0;
}

/*
 * Sets a value at index in the shvec with id
 * Appends 0s if the index is larger than the current size
 * Returns 0 on success and 1 on failure
 */

int shvec_set(int id, int index, int value){
    for(int i=shvec_array[id].size; i<index; i++){
        if(shvec_append(id, 0)){
            // error
            fprintf(stderr, "ERROR: could not resize array\n");
            return 1;
        }
    }
    shvec_array[id].data[index] = value;
    return 0;
}

/*
 * Returns the value at 'index' of shvec 'id'
 * If out of bounds, returns 0
 */

int shvec_get(int id, int index){
    if(index > shvec_array[id].size){
        fprintf(stderr, "ERROR: getting outside of array size\n");
        return 0;
    }
    return shvec_array[id].data[index];
}

/*
 * Frees the shvec with given 'id' from heap
 * Returns 0 on success, -1 on error
 */
int shvec_free(int id) {
    if(shvec_available[id] == 1){
        // shvfree(shvec_array[id].data);
        free(shvec_array[id].data);
        shvec_available[id] = 0;
        return 0;
    } else {
        fprintf(stderr, "KeyError: shvec with given id does not exist\n");
        return -1;
    }
}

/* 
 *
 * returns 0 for available, 1 for in use
 */
int shvec_is_available(int id) {
    if (id < MAX_SHVECS) {
        return shvec_available[id];
    } else {
        fprintf(stderr, "KeyError: id too large");
        return 0;
    }
}

int shvec_get_size(int id) {
    if (id > MAX_SHVECS) {
        fprintf(stderr, "KeyError: id too large");
        return 0;
    }

    if (shvec_is_available(id) == 0) {
        fprintf(stderr, "Err: Shvec id not in use");
    }

    return shvec_array[id].size;
}

int* shvec_get_array(int id){
    return shvec_array[id].data;
}

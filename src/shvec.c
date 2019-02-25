#include "shvec.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;        // number of initialized values
    int max_size;    // max number of values
    int *data_ptr;   // array of values
} Shvector;

Shvector shvec_array[MAX_SHVECS];
int shvec_available[MAX_SHVECS];

int shvec_initialize(int shvec_id){
    //todo: malloc error handling
    int* data_ptr = malloc(sizeof(int)*INIT_SIZE);
    shvec_array[shvec_id] = (Shvector) {.size=0, .max_size=INIT_SIZE, .data_ptr=data_ptr};
    shvec_available[shvec_id] = 1;
    return shvec_id;
}
/*
* Creates a new Shvec
* Returns a new Shvec id
*/
int shvec_create(){
    int shvec_id;
    for(shvec_id = 0; shvec_id < MAX_SHVECS; shvec_id++){
        if (shvec_available[shvec_id] == 0){
            return shvec_initialize(shvec_id);
        }
    }
    return -1;
}

int shvec_append(int id, int value){
    if(shvec_array[id].size < shvec_array[id].max_size){
        shvec_array[id].size++;
        shvec_array[id].data_ptr[shvec_array[id].size] = value;
        return 0;
    } else {
        // realloc and update max_size
        fprintf(stderr, "ERROR: could not resize array\n");
        return 1;
    }
}

int shvec_set(int id, int index, int value){
    for(int i=shvec_array[id].size; i<index; i++){
        if(shvec_append(id, 0)){
            // error
            fprintf(stderr, "ERROR: could not resize array\n");
            return 1;
        }
    }
    shvec_array[id].data_ptr[index] = value;
    return 0;
}

int shvec_get(int id, int index){
    if(index > shvec_array[id].size){
        fprintf(stderr, "ERROR: getting outside of array size\n");
        return 0;
    }
    return shvec_array[id].data_ptr[index];
}

int main(){
    int my_shvec = shvec_create();
    printf("shvec_id %d\n", my_shvec);

    printf("Setting [0] to 10\n");
    shvec_set(my_shvec, 0, 10);
    printf("value at [0]: %d\n", shvec_get(my_shvec, 0));
    printf("size of shvector %d\n", shvec_array[my_shvec].size);

    printf("Setting [5] to 5\n");
    shvec_set(my_shvec, 5, 5);
    printf("size of shvector %d\n", shvec_array[my_shvec].size);
    printf("value at [4]: %d\n", shvec_get(my_shvec, 4));
    printf("value at [5]: %d\n", shvec_get(my_shvec, 5));


    printf("TEST RESIZING:\n");
    printf("Setting [11] to 5\n");
    shvec_set(my_shvec, 11, 5);
    printf("size of shvector %d\n", shvec_array[my_shvec].size);
    printf("value at [11]: %d\n", shvec_get(my_shvec, 11));

    return 0;
}

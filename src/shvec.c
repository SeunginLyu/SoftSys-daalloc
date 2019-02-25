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
int shvec_free(int id){
    if(shvec_available[id] == 1){
        free(shvec_array[id].data_ptr);
        return 0;
    }
    return -1;
}
int main(){
    int my_shvec = shvec_create();
    printf("shvec_id %d\n", my_shvec);
    return 0;
}

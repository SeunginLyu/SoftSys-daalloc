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

int initialize_shvec(int shvec_id){
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
            return initialize_shvec(shvec_id);
        }
    }
    return -1;
}
int main(){
  int my_shvect = shvect_create();
  printf("shvec_id %d\n", my_shvect);

    return 0;
}

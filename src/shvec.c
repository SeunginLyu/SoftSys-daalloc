#include "shvec.h"
#include <stdio.h>

typedef struct {
  int size;        // number of initialized values 
  int max_size;    // max number of values
  int *data_ptr;   // array of values
} Shvector;

Shvector shvec_array[MAX_SHVECTS];

int main(){
    return 0;
}
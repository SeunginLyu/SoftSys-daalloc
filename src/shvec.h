// cap max_size to the maximum size of a power of 2 int
#define MAX_SHVECS 128
#define INIT_SIZE 8
#define GROWTH_FACTOR 2

int shvec_create();
int shvec_set(int id, int index, int value);
int shvec_get(int id, int index);
int shvec_free(int id);
int shvec_is_available(int id);

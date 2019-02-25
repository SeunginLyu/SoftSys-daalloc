# Shvector Spec

## Api:
`int shvec_create()`
Creates a new shvect and returns its `int shvec_id`

`shvec_set(int id, int index, int value)`
Set `value` at `index` of shvector `id`

`shvec_get(int id, int index)`
Get the value at `index` from shvector `id`
Index wraps around i.e. `-1` returns last value

`shvec_free(int id)`
Deletes the shvector `id` and frees the memory.

## Internal:
### #Defined:
```
GROWTH_FACTOR: the factor to expand an array when full
MAX_SHVECTS: the size of shvector_array (will remove when dynamically allocated)
INIT_SIZE: initial max_size of a new shvector
```

### Shvector struct
```
typedef struct {
  int size;        // number of initialized values
  int max_size;    // max number of values
  int *data_ptr;   // array of values
} Shvector;
```

### Functions
`_initialze(int shvect_id)`
allocates memory for a new array and initializes the values in shvect_array

`_append(schvector shvect, int value)`
appends `value` to shvect `id`, increments size. If `max_size > size`, it expands the array.

`_expand(shvector shvect)`
expands the array by the factor `GROWTH_FACTOR` and updates `max_size`

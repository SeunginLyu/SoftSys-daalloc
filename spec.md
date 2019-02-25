# Shvector Spec

## Api:
`int shvec_create()`
Creates a new shvect and returns its `int shvect_id`

`shvec_set(int id, int index)`
Set a value at `index` of shvector `id`

`shvec_get(int id,i int index)`
Get the value at `index` from shvector `id`
Index wraps around i.e. `-1` returns last value

`shvec_free(int id)`
Deletes the shvector `id` and frees the memory.

## Internal:
### #Defined:
```
GROWTH_FACTOR: the factor to expand an array when full
MAX_SHVECTS: the size of shvector_array (will remove when dynamically allocated)
```

### Shvector struct
```
typedef struct {
  int size;        // number of values so far
  int max_size;    // max length
  int *data_ptr;   // array of values
} Shvector;
```

### Functions
`_append(schvector shvect, int value)`
appends `value` to shvect `id`, increments size. If `max_size > size`, it expands the array.

`_expand(shvector shvect)`
expands the array by the factor `GROWTH_FACTOR` and updates `max_size`

#define META_SIZE sizeof(struct block_meta)

void shvfree(void *ptr);
void* shvalloc(size_t size);
struct block_meta *get_block_ptr(void *ptr);
struct block_meta *request_space(struct block_meta *last, size_t size);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta;
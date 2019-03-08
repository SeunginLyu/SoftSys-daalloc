#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "shvalloc.h"

void* global_base = NULL;

struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
    int magic; // for debugging only. TODO: remove this in non-debug mode
};

struct block_meta *find_free_block(struct block_meta **last, size_t size){
    struct block_meta *current = global_base;
    while(current && !(current->free && current->size >=size)){
        *last = current;
        current = current->next;
    }
    return current;
}
struct block_meta *request_space(struct block_meta *last, size_t size){
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void*)block == request); // NOT thread safe
    if (request == (void*) -1){
        return NULL; // sbrk failed
    }
    if (last) {
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;
    return block;
}
// shvec only deals with ints for now
void* shvalloc(size_t size){
    struct block_meta *block;
    // TODO : align size?
    if (size <= 0){
        return NULL;
    }
    if(!global_base){ // First call.
        block = request_space(NULL, size);
        if(!block){
            return NULL;
        }
        global_base = block;
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);
        if (!block){ // failed to find free block
            block = request_space(last, size);
            if (!block){
                return NULL;
            }
        } else {
            // TODO: consider splitting block here
            block->free = 0;
            block->magic = 0x77777777;
        }
    }
    // return the region after the struct block_meta
    return(block+1);
}
struct block_meta *get_block_ptr(void *ptr){
    return (struct block_meta*)ptr - 1;
}
void shvfree(void *ptr){
    if(!ptr){
        return;
    }
    // TODO: consider marging block once splitting blocks is implemented
    struct block_meta *block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free ==0);
    assert(block_ptr->magic==0x77777777 || block_ptr->magic == 0x12345678);
    block_ptr->free = 1;
    block_ptr->magic = 0x55555555;
}
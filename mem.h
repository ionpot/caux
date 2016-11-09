#ifndef MEM_H
#define MEM_H

void mem_init(size_t size);
void mem_destroy(void);
void *mem_alloc(size_t size);
void *mem_realloc(void *ptr, size_t size);
void *mem_expand(void *ptr, size_t new_size);
void mem_free(void *ptr);

#endif

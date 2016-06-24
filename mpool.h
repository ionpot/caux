#ifndef MPOOL_H
#define MPOOL_H

void mpool_init(void);
void mpool_destroy(void);
void *mpool_alloc(size_t size);
void *mpool_realloc(void *ptr, size_t size);
void mpool_free(void *ptr);

#endif

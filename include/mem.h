#ifndef MEM_H
#define MEM_H

#include "def.h"
#include "memnode.h"

typedef struct {
	size_t expansion;
	MemNode *first;
	MemNode *last;
	MemNode *first_avlb;
	MemNode *last_avlb;
} Mem;

caux mem_init(Mem *, size_t initial);
void mem_free(Mem *);

void * mem_next(Mem *, size_t request);

#endif

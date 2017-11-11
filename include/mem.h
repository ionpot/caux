#ifndef MEM_H
#define MEM_H

#include "def.h"
#include "memnode.h"

struct Mem {
	size_t expansion;
	struct MemNode *first;
	struct MemNode *last;
	struct MemNode *first_avlb;
	struct MemNode *last_avlb;
};

enum caux mem_init(struct Mem *, size_t initial);
void      mem_destroy(struct Mem *);

void * mem_next(struct Mem *, size_t request);

#endif

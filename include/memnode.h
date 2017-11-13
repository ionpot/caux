#ifndef MEMNODE_H
#define MEMNODE_H

#include "def.h"
#include "readbfr.h"

struct MemNode {
	struct MemNode *next;
	struct MemNode *next_avlb;
	struct ReadBuffer buffer;
};

struct MemNode * memnode_alloc(size_t);
struct MemNode * memnode_alloc_atleast(size_t min, size_t extra);

void * memnode_next(struct MemNode *, size_t);

int    memnode_has(struct MemNode *, size_t);
int    memnode_full(struct MemNode *);

#endif

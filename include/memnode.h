#ifndef MEMNODE_H
#define MEMNODE_H

#include "link.h"
#include "buffer.h"
#include "bufrdr.h"

struct MemNode {
	struct MemNode *next;
	struct MemNode *next_avlb;
	struct Buffer buffer;
	struct BufRdr reader;
};

struct MemNode * memnode_alloc(size_t *request);
bool             memnode_is_full(struct MemNode *);

#endif

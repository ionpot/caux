#ifndef MEMNODE_H
#define MEMNODE_H

#include "link.h"
#include "buffer.h"
#include "bufrdr.h"

typedef struct {
	Link next;
	Link next_avlb;
	Buffer buffer;
	BufRdr reader;
} MemNode;

MemNode * memnode_alloc(size_t *request);

#endif

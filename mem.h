#ifndef MEM_H
#define MEM_H

#include "def.h"

typedef struct {
	DLink link;
	Link next_a;
	BfrR rdr;
	Bfr bfr;
} MemSec;

typedef struct {
	MemSec *head;
	MemSec *tail;
	MemSec *avlb;
} Mem;

int mem_init(Mem *, size_t);
void mem_destroy(Mem *);

void * mem_next(Mem *, size_t);

#endif

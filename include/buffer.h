#ifndef BUFFER_H
#define BUFFER_H

#include "def.h"

struct Buffer {
	size_t size;
	byte * data;
};

void buffer_init(struct Buffer *, size_t, void *);

void * buffer_get(struct Buffer *, usgn i);
void   buffer_set(struct Buffer *, usgn i, byte);

int buffer_is_index(struct Buffer *, usgn i);
int buffer_is_size(struct Buffer *, size_t);

#endif

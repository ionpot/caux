#ifndef BUFFER_H
#define BUFFER_H

#include "def.h"

struct Buffer {
	size_t size;
	byte * data;
};

void buffer_init(struct Buffer *, size_t, void *);

void * buffer_get(const struct Buffer *, usgn i);
void   buffer_set(struct Buffer *, usgn i, byte);

int buffer_is_index(const struct Buffer *, usgn i);
int buffer_is_size(const struct Buffer *, size_t);

#endif

#ifndef BUFFER_H
#define BUFFER_H

#include "def.h"

struct Buffer {
	size_t size;
	byte *data;
};

void buffer_init(struct Buffer *, size_t, void *);

void * buffer_get(struct Buffer *, size_t);
void   buffer_set(struct Buffer *, size_t, byte);

int buffer_is_index(struct Buffer *, size_t);
int buffer_is_size(struct Buffer *, size_t);

#endif

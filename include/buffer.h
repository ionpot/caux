#ifndef BUFFER_H
#define BUFFER_H

#include "def.h"

typedef struct {
	size_t size;
	byte *data;
} Buffer;

void buffer_init(Buffer *, size_t, void *);

void * buffer_get(Buffer *, size_t);
void buffer_set(Buffer *, size_t, byte);

int buffer_is_index(Buffer *, size_t);
int buffer_is_size(Buffer *, size_t);

#endif

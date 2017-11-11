#include "buffer.h"

#include <assert.h>

void
buffer_init(struct Buffer *buf, size_t size, void *data)
{
	buf->size = size;
	buf->data = data;
}

void *
buffer_get(struct Buffer *buf, usgn i)
{
	assert(i < buf->size);

	return buf->data + i;
}

void
buffer_set(struct Buffer *buf, usgn i, byte val)
{
	byte *p = buffer_get(buf, i);

	*p = val;
}

int
buffer_is_index(struct Buffer *buf, usgn i)
{
	return i < buf->size;
}

int
buffer_is_size(struct Buffer *buf, size_t size)
{
	return size <= buf->size;
}

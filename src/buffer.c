#include "buffer.h"

#include <assert.h>

void
buffer_init(struct Buffer *buf, size_t size, void *data)
{
	buf->size = size;
	buf->data = data;
}

void *
buffer_get(struct Buffer *buf, size_t at)
{
	assert(at < buf->size);

	return buf->data + at;
}

void
buffer_set(struct Buffer *buf, size_t at, byte val)
{
	byte *p = buffer_get(buf, at);

	*p = val;
}

int
buffer_is_index(struct Buffer *buf, size_t index)
{
	return index < buf->size;
}

int
buffer_is_size(struct Buffer *buf, size_t size)
{
	return size <= buf->size;
}

#include "bfr.h"

#include <assert.h>

void
bfr_init(Bfr *buf, size_t size, void *data)
{
	buf->size = size;
	buf->data = data;
}

void *
bfr_get(Bfr *buf, size_t at)
{
	assert(at < buf->size);

	return buf->data + at;
}

void
bfr_set(Bfr *buf, size_t at, byte val)
{
	byte *p = bfr_get(buf, at);

	*p = val;
}

void
bfr_slice(Bfr *restrict src, Bfr *restrict dst, size_t at, size_t len)
{
	assert((at + len) <= src->size);

	bfr_init(dst, len, bfr_get(src, at));
}

void
bfr_skip(Bfr *restrict src, Bfr *restrict dst, size_t at)
{
	assert(at < src->size);

	size_t len = src->size - at;

	bfr_slice(src, dst, at, len);
}

void
bfr_cap(Bfr *restrict src, Bfr *restrict dst, size_t len)
{
	assert(len <= src->size);

	bfr_init(dst, len, src->data);
}

int
bfr_is_index(Bfr *buf, size_t index)
{
	return index < buf->size;
}

int
bfr_is_size(Bfr *buf, size_t size)
{
	return size <= buf->size;
}

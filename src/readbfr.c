#include "readbfr.h"

#include <assert.h>

void
readbfr_init(struct ReadBfr *rb, size_t size, void *data)
{
	assert(rb != NULL);

	buffer_init(&rb->buffer, size, data);

	readbfr_reset(rb);
}

void
readbfr_reset(struct ReadBfr *rb)
{
	assert(rb != NULL);

	rb->head = 0;
}

void *
readbfr_next(struct ReadBfr *rb, size_t size)
{
	assert(rb != NULL);

	void *addr = buffer_get(&rb->buffer, rb->head);

	rb->head += size;

	return addr;
}

int
readbfr_has(const struct ReadBfr *rb, size_t size)
{
	assert(rb != NULL);

	return buffer_is_size(&rb->buffer, rb->head + size);
}

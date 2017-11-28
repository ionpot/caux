#ifndef READBFR_H
#define READBFR_H

#include "buffer.h"
#include "def.h"

struct ReadBuffer {
	struct Buffer buffer;
	usgn head;
};

void   readbfr_init(struct ReadBuffer *, size_t, void *);
void   readbfr_reset(struct ReadBuffer *);
void * readbfr_next(struct ReadBuffer *, size_t);
int    readbfr_has(const struct ReadBuffer *, size_t);

#endif

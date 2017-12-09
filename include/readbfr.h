#ifndef READBFR_H
#define READBFR_H

#include "buffer.h"
#include "def.h"

struct ReadBfr {
	struct Buffer buffer;
	usgn head;
};

void   readbfr_init(struct ReadBfr *, size_t, void *);
void   readbfr_reset(struct ReadBfr *);
void * readbfr_next(struct ReadBfr *, size_t);
int    readbfr_has(const struct ReadBfr *, size_t);

#endif

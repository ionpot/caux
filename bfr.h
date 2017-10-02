#ifndef BFR_H
#define BFR_H

#include "byte.h"
#include "def.h"

typedef struct {
	size_t size;
	byte *data;
} Bfr;

void bfr_init(Bfr *, size_t, void *);

void * bfr_get(Bfr *, size_t);
void bfr_set(Bfr *, size_t, byte);

void bfr_slice(Bfr *, Bfr *, size_t, size_t);
void bfr_skip(Bfr *, Bfr *, size_t);
void bfr_cap(Bfr *, Bfr *, size_t);

int bfr_is_index(Bfr *, size_t);
int bfr_is_size(Bfr *, size_t);

#endif

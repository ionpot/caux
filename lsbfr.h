#ifndef LSBFR_H
#define LSBFR_H

#include "addr.h"
#include "bfr_r.h"
#include "def.h"

typedef struct {
	BfrR bufr;
	addr *avlb;
} LsBfr;

int lsbfr_alloc(LsBfr *, size_t, uint);
void lsbfr_free(LsBfr *);

void lsbfr_reset(LsBfr *);

addr *lsbfr_next(LsBfr *, size_t);

int lsbfr_has(LsBfr *, uint, size_t);

void lsbfr_take(LsBfr *, addr *);

#endif

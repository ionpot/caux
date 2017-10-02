#ifndef BFR_R_H
#define BFR_R_H

#include "bfr.h"

typedef struct {
	Bfr *bfr;
	size_t head;
} BfrR;

void bfrr_init(BfrR *, Bfr *);
void bfrr_reset(BfrR *);

int bfrr_has(BfrR *, size_t);
void * bfrr_peek(BfrR *);
void * bfrr_read(BfrR *, size_t);
byte bfrr_byte(BfrR *);

#endif

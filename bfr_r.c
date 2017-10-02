#include "bfr_r.h"

void
bfrr_init(BfrR *r, Bfr *buf)
{
	r->bfr = buf;

	bfrr_reset(r);
}

void
bfrr_reset(BfrR *r)
{
	r->head = 0;
}

int
bfrr_has(BfrR *r, size_t step)
{
	size_t size = r->head + step;

	return bfr_is_size(r->bfr, size);
}

void *
bfrr_peek(BfrR *r)
{
	return bfr_get(r->bfr, r->head);
}

void *
bfrr_read(BfrR *r, size_t step)
{
	void *addr = bfrr_peek(r);

	r->head += step;

	return addr;
}

byte
bfrr_byte(BfrR *r)
{
	byte *b = bfrr_read(r, 1);

	return *b;
}

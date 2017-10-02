#include "addr.h"

typedef struct {
	addr *adr;
} Addr;

void
addr_add(void *to, void *adr)
{
	assert(to != nil);
	assert(adr != nil);

	Addr *a = to;
	addr *b = adr;

	addr_put(b, a->adr);

	a->adr = b;
}

void
addr_rmv(void *from)
{
	assert(from != nil);

	Addr *a = from;

	a->adr = addr_next(a->adr);
}

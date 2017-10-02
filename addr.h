#ifndef ADDR_H
#define ADDR_H

#include "def.h"

#include <assert.h>
#include <inttypes.h>

typedef uintptr_t addr;

static inline addr
addr_next(addr a)
{
	addr *b = (addr *)a;

	assert(b != nil);

	return *b;
}

static inline void *
addr_read(addr a)
{
	return (addr *)a + 1;
}

static inline void
addr_add(addr *to, addr *adr)
{
	assert(to != nil);
	assert(adr != nil);

	*adr = *to;
	*to = (addr)adr;
}

static inline void
addr_rmv(addr *from)
{
	assert(from != nil);

	*from = addr_next(*from);
}

#endif

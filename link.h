#ifndef LINK_H
#define LINK_H

#include "def.h"

#include <assert.h>

typedef struct Link {
	struct Link *next;
} Link;

static inline void
link_add(Link *to, Link *ln)
{
	assert(to != nil);
	assert(ln != nil);

	ln->next = to->next;
	to->next = ln;
}

static inline void
link_rmv(Link *from, Link *ln)
{
	assert(from != nil);
	assert(ln != nil);

	from->next = ln->next;
}

#endif

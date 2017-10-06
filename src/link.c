#include "link.h"

#include "def.h"

#include <assert.h>

void
link_init(Link *ln)
{
	ln->next = NULL;
}

void
link_set(Link *ln, Link *prev)
{
	assert(prev != NULL);

	ln->next = prev->next;
	prev->next = ln;
}

void
link_unset(Link *ln, Link *prev)
{
	assert(prev != NULL);

	prev->next = ln->next;
}

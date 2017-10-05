#include "link.h"

#include "def.h"

void
link_init(Link *ln)
{
	ln->next = NULL;
}

void
link_set(Link *ln, Link *prev)
{
	ln->next = prev->next;
	prev->next = ln;
}

void
link_unset(Link *ln, Link *prev)
{
	prev->next = ln->next;
}

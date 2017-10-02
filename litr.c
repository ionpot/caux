#include "litr.h"

void
litr_init(LItr *itr, addr *a)
{
	itr->next = addr_next(a);
	itr->prev = a;
}

void
litr_next(LItr *itr)
{
	itr->prev = itr->next;
	itr->next = addr_next(itr->next);
}

void
litr_insert(LItr *itr, addr *a)
{
	addr_put(a, itr->next);
	addr_put(itr->prev, a);
}

void
litr_append(LItr *itr, addr *a)
{
	*a = *itr->next;

	addr_put(itr->next, a);
}

addr *
litr_remove(LItr *itr)
{
	*itr->prev = *itr->next;

	return itr->next;
}

void *
litr_read(LItr *itr)
{
	return addr_read(itr->next);
}

#include "list.h"

#include "dbg.h"

static addr *head_addr(List *);
static addr *tail_addr(List *);
static addr *next_avlb(List *);

int
list_alloc(List *ls, size_t item, uint count)
{
	size_t node = sizeof(addr) + item;
	int err = lsbfr_alloc(&ls->lsb, node, count);

	is_ok(err, "list_alloc(%zu, %zu) failed.", item, count);

	ls->node = node;

	list_clear(ls);
error:
	return err;
}

void
list_free(List *ls)
{
	lsbfr_free(&ls->lsb);
}

void
list_clear(List *ls)
{
	addr *end = tail_addr(ls);

	ls->head = end;
	ls->tail = end;

	lsbfr_reset(&ls->lsb);
}

void *
list_push(List *ls)
{
	addr *a = next_avlb(ls);

	if (list_empty(ls)) {
		ls->head = a;
	}

	addr_put(a, tail_addr(ls));
	addr_put(ls->tail, a);

	return addr_read(a);
}

void *
list_shift(List *ls)
{
	LItr itr;

	list_rewind(ls, &itr);

	return list_remove(ls, &itr);
}

void *
list_unshift(List *ls)
{
	LItr itr;

	list_rewind(ls, &itr);

	return list_insert(ls, &itr);
}

void *
list_insert(List *ls, LItr *itr)
{
	addr *a = next_avlb(ls);

	if (list_empty(ls)) {
		ls->tail = a;
	}

	litr_insert(itr, a);

	return addr_read(a);
}

void *
list_append(List *ls, LItr *itr)
{
	addr *a = next_avlb(ls);

	if (list_empty(ls)) {
		ls->head = a;
	}

	litr_append(itr, a);

	return addr_read(a);
}

void *
list_remove(List *ls, LItr *itr)
{
	addr *a = litr_remove(itr);

	lsbfr_take(&ls->lsb, a);

	return addr_read(a);
}

void
list_rewind(List *ls, LItr *itr)
{
	litr_init(itr, head_addr(ls));
}

int
list_end(List *ls, LItr *itr)
{
	return itr->next == tail_addr(ls);
}

int
list_empty(List *ls)
{
	return ls->head == tail_addr(ls);
}

/* static */
addr *
head_addr(List *ls)
{
	return (addr *)&ls->head;
}

addr *
tail_addr(List *ls)
{
	return (addr *)&ls->tail;
}

addr *
next_avlb(List *ls)
{
	return lsbfr_next(&ls->lsb, ls->node);
}

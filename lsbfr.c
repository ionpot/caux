#include "lsbfr.h"

#include "dbg.h"

static int avlb_has(LsBfr *, uint *);
static addr *pop_avlb(LsBfr *);

int
lsbfr_alloc(LsBfr *lb, size_t item, uint count)
{
	size_t total = item * count;
	int err = bfrr_alloc(&lb->bufr, total);

	is_ok(err, "lsbfr_alloc(%zu) failed.", total);

	lsbfr_reset(lb);

	return 0;
error:
	return err;
}

void
lsbfr_free(LsBfr *lb)
{
	bfrr_free(&lb->bufr);
}

void
lsbfr_reset(LsBfr *lb)
{
	lb->avlb = nil;

	bfrr_reset(&lb->bufr);
}

int
lsbfr_has(LsBfr *lb, uint count, size_t node)
{
	if (avlb_has(lb, &count)) {
		return 1;
	}

	return bfrr_has(&lb->bufr, count * node);
}

addr *
lsbfr_next(LsBfr *lb, size_t node)
{
	return lb->avlb
		? pop_avlb(lb)
		: bfrr_read(&lb->bufr, node);
}

void
lsbfr_take(LsBfr *lb, addr *a)
{
	addr_put(a, lb->avlb);

	lb->avlb = a;
}

/* static */
int
avlb_has(LsBfr *lb, uint *count)
{
	addr *a = lb->avlb;
	uint i = *count;

	while (a) {
		i -= 1;

		if (i) {
			a = addr_next(a);

		} else {
			return 1;
		}
	}

	*count = i;

	return 0;
}

addr *
pop_avlb(LsBfr *lb)
{
	addr *a = lb->avlb;

	lb->avlb = addr_next(a);

	return a;
}

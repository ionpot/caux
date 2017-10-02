#include "stack.h"

#include "dbg.h"

int
stk_alloc(Stack *st, size_t size, size_t count)
{
	size_t total = size * count;
	int err = bfr_alloc(&st->buf, total);

	is_ok(err, "stk_alloc(%zu) failed.", total);

	st->length = 0;
	st->size = size;

	return 0;
error:
	return -1;
}

void
stk_free(Stack *st)
{
	bfr_free(&st->buf);

	st->length = 0;
}

int
stk_more(Stack *st, size_t i)
{
	size_t cur = st->size * st->length;
	size_t add = st->size * i;

	return bfr_is_size(&st->buf, cur + add);
}

int
stk_full(Stack *st)
{
	return stk_more(st, 1);
}

void *
stk_at(Stack *st, size_t at)
{
	return bfr_get(&st->buf, st->size * at);
}

void *
stk_top(Stack *st)
{
	return stk_at(st, st->length - 1);
}

void *
stk_push(Stack *st)
{
	st->length += 1;

	return stk_top(st);
}

void *
stk_pop(Stack *st)
{
	void *out = stk_top(st);

	st->length -= 1;

	return out;
}

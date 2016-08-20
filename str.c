#include <stdio.h>

#include "def.h"
#include "mem.h"

#include "str.h"

/* declare */
static size_t remaining(Str *);
static char *get_buf(Str *);
static void concat(Str *, const Str *src);
static void expand(Str *);

/* define */
void
str_init(Str *s, size_t size)
{
	s->buf = mem_alloc(size);
	s->size = size;
	s->length = 0;
}

void
str_free(Str *s)
{
	mem_free(s->buf);

	s->buf = nil;
	s->size = 0;
	s->length = 0;
}

void
str_clear(Str *s)
{
	s->length = 0;
}

void
str_ch(Str *s, char b)
{
	size_t len = s->length;

	if (len == s->size)
		expand(s);

	s->buf[len] = b;
	s->length = len + 1;
}

void
str_put(Str *s, const char *chars)
{
	int i = 0;
	char c = chars[i];

	while (c != '\0') {
		str_ch(s, c);

		c = chars[++i];
	}
}

void
str_putf(Str *s, const char *fmt, void *arg)
{
	size_t rem = remaining(s);
	int w;

	if (!rem) {
		goto exp;
	}

	w = snprintf(get_buf(s), rem, fmt, arg);

	if ((w + 1) < rem) {
		s->length += w;

		return;
	}
exp:
	expand(s);

	str_putf(s, fmt, arg);
}

void
str_concat(Str *s, const Str *src)
{
	if (src->length < remaining(s)) {
		concat(s, src);

	} else {
		expand(s);

		str_concat(s, src);
	}
}

void
str_echo(Str *s)
{
	fwrite(s->buf, 1, s->length, stdout);
}

/* static */
size_t
remaining(Str *s)
{
	if (s->length < s->size)
		return s->size - s->length;

	return 0;
}

char *
get_buf(Str *s)
{
	return s->buf + s->length;
}

void
concat(Str *s, const Str *src)
{
	char *buf = get_buf(s);
	size_t len = src->length;
	size_t i = 0;

	while (i < len) {
		buf[i] = src->buf[i];

		i += 1;
	}

	s->length += len;
}

void
expand(Str *s)
{
	size_t sz = s->size * 2;

	s->buf = mem_realloc(s->buf, sz);
	s->size = sz;
}

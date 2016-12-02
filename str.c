#include <stdio.h>
#include <stdarg.h>

#include "def.h"
#include "mem.h"

#include "str.h"

/* declare */
static int remaining(Str *);
static char *get_buf(Str *);
static void concat(Str *, const Str *src);

/* define */
int
str_init(Str *s, int size)
{
	s->buf = mem_alloc((size_t)size);
	s->size = size;
	s->length = 0;

	return s->buf ? 0 : -1;
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

int
str_ch(Str *s, char b)
{
	int len = s->length;

	if (len < s->size) {
		s->buf[len] = b;
		s->length = len + 1;

		return 1;
	}

	return 0;
}

int
str_put(Str *s, const char *chars)
{
	int i = 0;
	char c = chars[i];

	while (c != '\0') {
		str_ch(s, c);

		c = chars[i];

		i += 1;
	}

	return i;
}

int
str_putf(Str *s, const char *fmt, ...)
{
	int rem = remaining(s);

	if (!rem)
		return -1;

	va_list args;
	va_start(args, fmt);

	int w = vsnprintf(get_buf(s), (size_t)rem, fmt, args);

	va_end(args);

	if ((w + 1) < rem) {
		s->length += w;

		return 0;
	}

	return -1;
}

int
str_concat(Str *s, const Str *src)
{
	if (src->length < remaining(s)) {
		concat(s, src);

		return 0;
	}

	return -1;
}

void
str_echo(Str *s)
{
	fwrite(s->buf, (size_t)1, (size_t)s->length, stdout);
}

/* static */
int
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
	int len = src->length;
	int i = 0;

	while (i < len) {
		buf[i] = src->buf[i];

		i += 1;
	}

	s->length += len;
}

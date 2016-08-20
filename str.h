#ifndef STR_H
#define STR_H

typedef struct {
	char *buf;
	size_t size;
	size_t length;
} Str;

void str_init(Str *, size_t size);
void str_free(Str *);
void str_reset(Str *);

void str_ch(Str *, char ch);
void str_put(Str *, const char *str);
void str_putf(Str *, const char *fmt, void *arg);
void str_concat(Str *, const Str *src);
void str_echo(Str *);

#endif

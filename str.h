#ifndef STR_H
#define STR_H

typedef struct {
	char *buf;
	int size;
	int length;
} Str;

int str_init(Str *, int size);
void str_free(Str *);
void str_clear(Str *);

int str_ch(Str *, char ch);
int str_put(Str *, const char *str);
int str_putf(Str *, const char *fmt, ...);
int str_concat(Str *, const Str *src);

int str_read(Str *, FILE *);
int str_write(Str *, FILE *);

void str_echo(Str *);

#endif

#ifndef FR_H
#define FR_H

typedef struct {
	FILE *f;
	size_t read;
} FileR;

int fr_open(FileR *, const char *);
void fr_close(FileR *);

void fr_read(FileR *, Bfr *);

void fr_cap(FileR *, Bfr *, Bfr *);

#endif

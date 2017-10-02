#include "def.h"
#include "dbg.h"
#include "bfr.h"

#include "fr.h"

int
fr_open(FileR *fr, const char *path)
{
	FILE *f = fopen(path, "rb");

	not_nil(f, "fr_open(%s) failed.", path);

	fr->f = f;

	return 0;
error:
	return -1;
}

void
fr_close(FileR *fr)
{
	fclose(fr->f);

	fr->f = nil;
}

void
fr_read(FileR *fr, Bfr *buf)
{
	size_t count = 1;
	size_t max = buf->size;

	fr->read = fread(buf->data, count, max, fr->f);
}

void
fr_cap(FileR *fr, Bfr *buf, Bfr *nbuf)
{
	bfr_cap(buf, nbuf, fr->read);
}

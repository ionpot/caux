#include "str.h"
#include "fs.h"

void
fs_read(char *path, int size, fs_read_cb f, void *v)
{
	Str str;

	str_init(&str, size);
}

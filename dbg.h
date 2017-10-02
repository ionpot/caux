#ifndef DBG_H
#define DBG_H

#include "byte.h"
#include "def.h"
#include "err.h"

#include <assert.h>

#define dbg_if(S) \
	DOWL(if (DEBUG) { S })

#define dbg_print(M, ...) \
	err_print("D", M, ##__VA_ARGS__)

#define dbg_echo(M, ...) \
	dbg_print(M "\n", ##__VA_ARGS__)

#define log_d(M, ...) dbg_if(\
	dbg_echo(M, ##__VA_ARGS__);)

#define log_hex(B, C) dbg_if(\
	dbg_print("hex_dump(%s, %zu):", #B, C);\
	dbg_hexd(B, C);)

static inline void
dbg_hexd(void *v, size_t size)
{
	assert(v != nil);

	byte *b = v;
	uint i = 0;

	while (i < size) {
		err_write(" %2x", b[i++]);
	}

	err_write("\n");
}

#endif

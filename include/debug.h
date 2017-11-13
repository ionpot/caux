#ifndef DEBUG_H
#define DEBUG_H

#include "def.h"

#include <assert.h>
#include <stdio.h>

#ifdef NDEBUG
#define DEBUG 0
#else
#define DEBUG 1
#endif

#define debug_if(S) \
	DOWL(if (DEBUG) { S })

#define debug_print(M, ...) \
	fprintf(stderr, M, ##__VA_ARGS__)

#define debug_prefix(M, ...) \
	debug_print("[%s:%d] " M, __FILE__, __LINE__, ##__VA_ARGS__)

#define debug(M, ...) debug_if(\
	debug_prefix(M "\n", ##__VA_ARGS__);)

#define debug_buffer(B) debug_if(\
	debug_prefix("buffer(%s, %zu):", #B, (B)->size);\
	debug_hexd((B)->data, (B)->size);)

static inline void
debug_hexd(void *data, size_t size)
{
	assert(data != NULL);

	byte *b = (byte *)data;
	usgn i = 0;

	while (i < size)
		debug_print(" %02x", b[i++]);

	debug_print("\n");
}

#endif

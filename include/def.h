#ifndef DEF_H
#define DEF_H

#include <stddef.h>

#define DOWL(x) \
	do { x } while (0)

#ifndef offsetof
#define offsetof(TYPE, MEMBER) \
	((size_t) &((TYPE *)0)->MEMBER)
#endif

#define struct_of(PTR, TYPE, MEMBER) \
	((TYPE *)((char *)(1 ? PTR : &((TYPE *)0)->MEMBER)\
	- offsetof(TYPE, MEMBER)))

#define jump_if_null(PTR, LABEL) DOWL(\
	if ((PTR) == NULL) goto LABEL;)

typedef unsigned char byte;
typedef size_t uint;

typedef enum {
	CAUX_OK,
	CAUX_NO_MEM
} caux;

#endif

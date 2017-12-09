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

#define jump_if(COND, LABEL) \
	DOWL(if (COND) goto LABEL;)

#define jump_ifnull(PTR, LABEL) \
	jump_if((PTR) == NULL, LABEL)

typedef unsigned char byte;
typedef size_t usgn;

enum caux {
	CAUX_OK = 0,
	CAUX_NO_MEM
};

#endif

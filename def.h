#ifndef DEF_H
#define DEF_H

#include <stddef.h>

#define nil NULL

#define DOWL(x) \
	do { x } while (0)

#ifndef offsetof
#define offsetof(TYPE, MEMBER) \
	((size_t) &((TYPE *)0)->MEMBER)
#endif

#define container_of(PTR, TYPE, MEMBER) \
	((TYPE *)((char *)(1 ? PTR : &((TYPE *)0)->MEMBER)\
	- offsetof(TYPE, MEMBER)))

typedef size_t uint;

#endif

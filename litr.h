#ifndef LITR_H
#define LITR_H

#include "addr.h"

typedef struct {
	addr *next;
	addr *prev;
} LItr;

void litr_init(LItr *, addr *);

void litr_next(LItr *);

void litr_insert(LItr *, addr *);
void litr_append(LItr *, addr *);

addr *litr_remove(LItr *);

void *litr_read(LItr *);

#endif

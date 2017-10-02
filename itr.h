#ifndef ITR_H
#define ITR_H

#include "link.h"

typedef struct {
	Link *next;
	Link *prev;
} Itr;

void itr_init(Itr *, Link *);

void itr_next(Itr *);

void itr_insert(Itr *, Link *);
void itr_append(Itr *, Link *);

Link *itr_remove(Itr *);

void *itr_read(Itr *);

#endif

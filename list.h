#ifndef LIST_H
#define LIST_H

#include "addr.h"
#include "def.h"
#include "litr.h"
#include "lsbfr.h"

typedef struct {
	LsBfr lsb;
	addr *head;
	addr *tail;
	size_t node;
} List;

int list_alloc(List *, size_t, uint);
void list_free(List *);

void list_clear(List *);

void *list_push(List *);
void *list_shift(List *);
void *list_unshift(List *);

void *list_insert(List *, LItr *);
void *list_append(List *, LItr *);
void *list_remove(List *, LItr *);

void list_rewind(List *, LItr *);
int list_end(List *, LItr *);

int list_empty(List *);
int list_end_addr(List *, addr *);

#endif

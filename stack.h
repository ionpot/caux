#ifndef STACK_H
#define STACK_H

#include "bfr.h"

typedef struct {
	Bfr buf;
	size_t length;
	size_t size;
} Stack;

int stk_alloc(Stack *, size_t, size_t);
void stk_free(Stack *);

int stk_more(Stack *, size_t);
int stk_full(Stack *);

void *stk_at(Stack *, size_t);
void *stk_top(Stack *);

void *stk_push(Stack *);
void *stk_pop(Stack *);

#endif

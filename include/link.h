#ifndef LINK_H
#define LINK_H

typedef struct Link {
	struct Link *next;
} Link;

void link_init(Link *);

void link_set(Link *, Link *prev);
void link_unset(Link *, Link *prev);

#endif

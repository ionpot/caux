#ifndef LINK_H
#define LINK_H

#include "def.h"

#include <assert.h>

#define link_unset_member(MEMBER, LINK, PREV) DOWL(\
	assert((LINK) != NULL);\
	assert((PREV) != NULL);\
	(PREV)->MEMBER = (LINK)->MEMBER;)

#endif

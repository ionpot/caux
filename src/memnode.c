#include "memnode.h"

#include "def.h"

#include <assert.h>
#include <stdlib.h>

static void
init_node(MemNode *node, size_t size)
{
	assert(node != NULL);
	assert(size > sizeof(MemNode));

	size_t buf_sz = size - sizeof(MemNode);

	link_init(&node->next);
	link_init(&node->next_avail);

	readbfr_init(&node->buffer, buf_sz, node + 1);
}

MemNode *
memnode_alloc(size_t *request)
{
	assert(request != NULL);

	MemNode *node = malloc(*request);

	jump_if_null(node, no_mem);

	init_node(node, *request);

	return node;

no_mem:
	*request >>= 1;

	return (*request > sizeof(MemNode))
		? memnode_alloc(request)
		: NULL;
}

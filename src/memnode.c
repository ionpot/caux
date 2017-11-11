#include "memnode.h"

#include <assert.h>
#include <stdlib.h>

#define MIN_NODE_SIZE sizeof(int)

static void
init_node(struct MemNode *node, size_t size)
{
	assert(node != NULL);
	assert(size > MIN_NODE_SIZE);

	node->next = NULL;
	node->next_avlb = NULL;

	readbfr_init(&node->buffer, size, node + 1);
}

struct MemNode *
memnode_alloc(size_t request)
{
	if (request < MIN_NODE_SIZE)
		return NULL;

	struct MemNode *node =
		malloc(request + sizeof(struct MemNode));

	if (node == NULL)
		return memnode_alloc(request >> 1);

	init_node(node, request);

	return node;
}

void *
memnode_next(struct MemNode *node, size_t size)
{
	assert(node != NULL);
	assert(size > 0);

	return readbfr_next(&node->buffer, size);
}

int
memnode_has(struct MemNode *node, size_t size)
{
	assert(node != NULL);
	assert(size > 0);

	return readbfr_has(&node->buffer, size);
}

int
memnode_full(struct MemNode *node)
{
	assert(node != NULL);

	return !readbfr_has(&node->buffer, MIN_NODE_SIZE);
}

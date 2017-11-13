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

static struct MemNode *
alloc_node(size_t request)
{
	struct MemNode *node =
		malloc(request + sizeof(struct MemNode));

	if (node != NULL)
		init_node(node, request);

	return node;
}

static struct MemNode *
alloc_atleast(size_t minimum, size_t extra)
{
	if (extra < 2)
		extra = 0;

	struct MemNode *node = alloc_node(minimum + extra);

	if (node == NULL)
		if (extra)
			return alloc_atleast(minimum, extra >> 1);

	return node;
}

struct MemNode *
memnode_alloc(size_t request)
{
	if (request < MIN_NODE_SIZE)
		return NULL;

	struct MemNode *node = alloc_node(request);

	if (node == NULL)
		return memnode_alloc(request >> 1);

	return node;
}

struct MemNode *
memnode_alloc_atleast(size_t minimum, size_t extra)
{
	if (minimum < MIN_NODE_SIZE)
		minimum = MIN_NODE_SIZE;

	return alloc_atleast(minimum, extra);
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

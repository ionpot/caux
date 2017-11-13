#include "mem.h"

#include <assert.h>
#include <stdlib.h>

static void
append(struct Mem *mem, struct MemNode *node)
{
	assert(mem != NULL);
	assert(node != NULL);

	struct MemNode *last = mem->last;
	struct MemNode *last_avlb = mem->last_avlb;

	assert(last != NULL);
	assert(last_avlb != NULL);

	last->next = node;
	last_avlb->next_avlb = node;

	mem->last = node;
	mem->last_avlb = node;
}

static void
rmv_avlb(struct Mem *mem, struct MemNode *node, struct MemNode **prev)
{
	assert(mem != NULL);
	assert(node != NULL);
	assert(prev != NULL);

	if (node == mem->last_avlb)
		mem->last_avlb = *prev;

	*prev = node->next_avlb;
}

static void *
add_space(struct Mem *mem, size_t request)
{
	assert(mem != NULL);

	struct MemNode *node =
		memnode_alloc_atleast(request, mem->expansion);

	if (node != NULL) {
		append(mem, node);

		return memnode_next(node, request);
	}

	return node;
}

static void *
find_space(struct Mem *mem, size_t request)
{
	assert(mem != NULL);

	struct MemNode *node = mem->first_avlb;
	struct MemNode **prev = &mem->first_avlb;

	while (node != NULL) {
		if (memnode_has(node, request))
			return memnode_next(node, request);

		if (memnode_full(node))
			rmv_avlb(mem, node, prev);

		prev = &node->next_avlb;
		node = node->next_avlb;
	}

	return NULL;
}

static void
free_nodes(struct MemNode *node)
{
	struct MemNode *next;

	if (node == NULL)
		return;

	next = node->next;

	free(node);

	free_nodes(next);
}

/* export */
enum caux
mem_init(struct Mem *mem, size_t initial)
{
	assert(mem != NULL);

	struct MemNode *node = memnode_alloc(initial);

	jump_if_null(node, no_mem);

	mem->expansion = initial;
	mem->first = node;
	mem->last = node;
	mem->first_avlb = node;
	mem->last_avlb = node;

	return CAUX_OK;

no_mem:
	return CAUX_NO_MEM;
}

void
mem_destroy(struct Mem *mem)
{
	assert(mem != NULL);

	free_nodes(mem->first);
}

void *
mem_next(struct Mem *mem, size_t request)
{
	assert(mem != NULL);
	assert(request > 0);

	if (request > mem->expansion)
		return add_space(mem, request);

	void *found = find_space(mem, request);

	return (found == NULL)
		? add_space(mem, request)
		: found;
}

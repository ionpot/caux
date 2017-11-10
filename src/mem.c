#include "mem.h"

#include <assert.h>

static void
append(struct Mem *mem, struct MemNode *node)
{
	assert(mem != NULL);
	assert(node != NULL);

	struct MemNode *last = mem->last;
	struct MemNode *last_av = mem->last_av;

	link_set(&node->next, &last->next);
	link_set(&node->next, &last_av->next);
}

static struct MemNode *
add_node(struct Mem *mem, size_t request)
{
	assert(mem != NULL);

	struct MemNode *node = memnode_alloc(mem->expansion);

	if (node != NULL) {
		append(mem, node);
	}

	return node;
}

static void *
add_node_next(struct Mem *mem, size_t request)
{
	struct MemNode *node = add_node(mem, request);

	return (node == NULL)
		? NULL
		: memnode_next(node, request);
}

static void
set_unavlb(struct Mem *mem, struct MemNode *node, struct MemNode *prev)
{
	struct MemNode *next = NULL;

	if (node == mem->first_avlb) {
		next = node->next_avlb;

		if (node == mem->last_avlb)
			mem->last_avlb = next;

		mem->first_avlb = next;

	} else {
		link_unset_member(next_avlb, node, prev);
	}
}

static void *
find_space(struct Mem *mem, size_t request)
{
	assert(mem != NULL);

	struct MemNode *node = mem->first_avlb;
	struct MemNode *prev = NULL;
	void *found = NULL;

	while (node != NULL) {
		found = memnode_alloc(node, request);

		if (found != NULL) {
			if (memnode_is_full(node)) {
				set_unavlb(mem, node, prev);
			}

			break;
		}

		prev = node;
		node = node->next_avlb;
	}

	return found;
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

static struct MemNode *
try_alloc(size_t size)
{
	if (size < MIN_NODE_SIZE)
		return NULL;

	struct MemNode *node = malloc(size + sizeof(struct MemNode));

	return (node == NULL)
		? try_alloc(size >> 1)
		: node;
}

/* export */
enum caux
mem_init(struct Mem *mem, size_t initial)
{
	assert(mem != NULL);
	assert(initial > MIN_NODE_SIZE);

	struct MemNode *node = try_alloc(initial);

	jump_if_null(node, no_mem);

	mem->expansion = initial;
	mem->first = node;
	mem->last = node;
	mem->first_av = node;
	mem->last_av = node;

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

	void *found = find_space(mem, request);

	return (found == NULL)
		? add_space(mem, request)
		: found;
}

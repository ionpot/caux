#include "mem.h"

#include <assert.h>

static void
append(Mem *mem, MemNode *node)
{
	MemNode *last = mem->last;
	MemNode *last_av = mem->last_av;

	link_set(&node->next, &last->next);
	link_set(&node->next, &last_av->next);
}

static MemNode *
add_node(Mem *mem, size_t request)
{
	MemNode *node = memnode_alloc(mem->expansion);

	if (node != NULL) {
		append(mem, node);
	}

	return node;
}

static void *
add_node_next(Mem *mem, size_t request)
{
	MemNode *node = add_node(mem, request);

	return (node == NULL)
		? NULL
		: memnode_next(node, request);
}

static void
set_unavlb(Mem *mem, MemNode *node, MemNode *prev)
{
	MemNode *next = NULL;

	if (node == mem->first_avlb) {
		next = memnode_next_avlb(node);

		if (node == mem->last_avlb) {
			mem->last_avlb = next;
		}

		mem->first_avlb = next;

	} else {
		assert(prev != NULL);

		memnode_set_unavlb(node, prev);
	}
}

static void *
find_space(Mem *mem, size_t request)
{
	MemNode *node = mem->first_avlb;
	MemNode *prev = NULL;
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
		node = memnode_next_avlb(node);
	}

	return found;
}

/* export */
caux
mem_init(Mem *mem, size_t initial)
{
	assert(initial > sizeof(MemNode));

	MemNode *node = memnode_alloc(initial);

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
mem_free(Mem *mem)
{
	MemNode *node = mem->first;
	Link link = first->next;

	free(node);

	while (link != NULL) {
		node = struct_of(link, MemNode, next);
		link = link.next;

		free(node);
	}
}

void *
mem_next(Mem *mem, size_t request)
{
	assert(request > 0);

	void *found = find_space(mem, request);

	return (found == NULL)
		? add_node_next(mem, request)
		: found;
}

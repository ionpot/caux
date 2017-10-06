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

	return node
		? memnode_next(node, request)
		: NULL;
}

status
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

	return STATUS_OK;

no_mem:
	return STATUS_NO_MEM;
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

	void *next = memnode_next(mem->first_av, request);

	return (next == NULL)
		? add_node_next(mem, request)
		: next;
}

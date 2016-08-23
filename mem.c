#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "mem.h"

#define MAX_POOLS 32
#define NODE_SIZE sizeof(Node)
#define MIN_SIZE (NODE_SIZE + 8)
#define NODE_OF(a) ((Node *)(a) - 1)

typedef struct Node {
	size_t size;
	struct Node *next;
} Node;

/* declare */
static void new_pool(size_t size);
static void *seek(size_t size);
static void *exact(Node *node, Node **prev);
static void *split(Node *node, size_t size, Node **prev);

/* local */
static Node *available = nil;
static struct {
	void *bufs[MAX_POOLS];
	int count;
	size_t next_size;
} pools;

/* define */
void
mem_init(size_t size)
{
	pools.count = 0;

	new_pool(size);
}

void
mem_destroy(void)
{
	int i = pools.count;
	void **bufs = pools.bufs;

	while (i > 0) {
		i -= 1;

		free(bufs[i]);

		bufs[i] = nil;
	}

	pools.count = 0;
	available = nil;
}

void *
mem_alloc(size_t size)
{
	size_t nsize = pools.next_size;
	void *ptr = seek(size);

	if (ptr)
		return ptr;

	while (nsize < size)
		nsize *= 2;

	new_pool(nsize);

	return mem_alloc(size);
}


void *
mem_realloc(void *src, size_t size)
{
	void *dst = mem_alloc(size);
	Node *node = NODE_OF(src);
	size_t sz = MIN(size, node->size);

	memcpy(dst, src, sz);

	return dst;
}

void
mem_free(void *ptr)
{
	Node *node = NODE_OF(ptr);
	node->next = available;
	available = node;
}

/* static */
void
new_pool(size_t size)
{
	int count = pools.count;
	Node *node = nil;

	if (count < MAX_POOLS)
		node = malloc(size);

	if (node == nil)
		exit(0);

	node->size = size - NODE_SIZE;
	node->next = nil;

	pools.bufs[count] = node;
	pools.count = count + 1;
	pools.next_size = size * 2;

	node->next = available;
	available = node;
}

void *
seek(size_t size)
{
	size_t size_found = 0;

	Node *node = available;
	Node **prev = &available;

	while (node) {
		size_found = node->size;

		if (size_found == size)
			return exact(node, prev);

		if (size_found > size) {
			if (size_found > MIN_SIZE)
				return split(node, size, prev);

			return exact(node, prev);
		}

		prev = &node->next;
		node = node->next;
	}

	return nil;
}

void *
exact(Node *node, Node **prev)
{
	void *addr = node + 1;

	*prev = node->next;

	return addr;
}

void *
split(Node *node, size_t size, Node **prev)
{
	size_t need = size + NODE_SIZE;

	byte *ptr = (byte *)node + need;
	Node *new_node = (Node *)ptr;

	new_node->size = node->size - need;
	new_node->next = node->next;

	*prev = new_node;

	return node + 1;
}

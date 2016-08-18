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
static Node *new_pool(void);
static void expand_pool(size_t size);
static void *seek(size_t size);
static void *exact(Node *node, Node **prev);
static void *split(Node *node, size_t size, Node **prev);

/* local */
static Node *available = nil;
static void *pools[MAX_POOLS];
static int pool_count = 0;
static size_t next_pool_size = KiB(4);

/* define */
void
mem_init(void)
{
	Node *node = new_pool();
	node->next = nil;
	available = node;
}

void
mem_destroy(void)
{
	while (pool_count > 0) {
		pool_count -= 1;

		free(pools[pool_count]);

		pools[pool_count] = nil;
	}

	available = nil;
}

void *
mem_alloc(size_t size)
{
	void *ptr = seek(size);

	if (ptr) {
		return ptr;
	}

	expand_pool(size);

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
Node *
new_pool(void)
{
	Node *node = nil;

	if (pool_count < MAX_POOLS) {
		node = malloc(next_pool_size);
	}

	if (node) {
		node->size = next_pool_size - NODE_SIZE;
		node->next = nil;

		pools[pool_count] = node;

		pool_count += 1;
		next_pool_size *= 2;

	} else {
		exit(0);
	}

	return node;
}

void
expand_pool(size_t size)
{
	Node *node = nil;

	while (next_pool_size < size) {
		next_pool_size *= 2;
	}

	node = new_pool();

	node->next = available;
	available = node;
}

void *
seek(size_t size)
{
	size_t size_found = 0;

	Node *node = available;
	Node **prev = &available;

	while (node)  {
		size_found = node->size;

		if (size_found == size) {
			return exact(node, prev);
		}

		if (size_found > size) {
			if (size_found > MIN_SIZE) {
				return split(node, size, prev);
			}

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

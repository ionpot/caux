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
static Node *new_pool(size_t size);
static Node *seek(size_t size);
static void nodes_add(Node *);
static Node *nodes_rmv(void);
static Node *nodes_rewind(void);
static Node *nodes_next(void);
static void nodes_split(size_t size);

/* local */
static struct {
	void *bufs[MAX_POOLS];
	int count;
	size_t next_size;
} pools;

static struct {
	Node *first;
	Node *head;
	Node **prev;
} nodes;

/* define */
void
mem_init(size_t size)
{
	pools.count = 0;

	nodes.first = new_pool(size);
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
	nodes.first = nil;
}

void *
mem_alloc(size_t size)
{
	size_t nsize = pools.next_size;
	Node *node = seek(size);

	if (node)
		return node + 1;

	while (nsize < size)
		nsize *= 2;

	node = new_pool(nsize);

	nodes_add(node);

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

	nodes_add(node);
}

/* static */
Node *
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

	nodes_add(node);

	return node;
}

Node *
seek(size_t size)
{
	Node *node = nodes_rewind();
	size_t size_found = 0;

	while (node) {
		size_found = node->size;

		if (size_found == size)
			return nodes_rmv();

		if (size_found > size) {
			if (size_found > MIN_SIZE)
				nodes_split(size);

			return nodes_rmv();
		}

		node = nodes_next();
	}

	return nil;
}

void
nodes_add(Node *node)
{
	node->next = nodes.first;
	nodes.first = node;
}

Node *
nodes_rmv(void)
{
	Node *head = nodes.head;

	nodes.head = head->next;
	*(nodes.prev) = nodes.head;

	return head;
}

Node *
nodes_rewind(void)
{
	Node *node = nodes.first;

	nodes.head = node;

	return node;
}

Node *
nodes_next(void)
{
	Node *node = nodes.head;

	nodes.head = node->next;
	nodes.prev = &node->next;

	return nodes.head;
}

void
nodes_split(size_t size)
{
	Node *head = nodes.head;
	size_t need = size + NODE_SIZE;
	char *ptr = (char *)head + need;
	Node *new_node = (Node *)ptr;

	new_node->size = head->size - need;
	new_node->next = head->next;

	head->size = size;
	head->next = new_node;
}

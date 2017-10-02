#include "mem.h"

#include "bfr.h"
#include "bfr_r.h"
#include "err.h"
#include "dlink.h"
#include "num.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MIN_SIZE 8

static MemSec * new_section(size_t);

int
mem_init(Mem *mem, size_t size)
{
	assert(size > MIN_SIZE);

	MemSec *sec = new_section(total);

	nil_ret(sec, -1);

	dlink_init(&sec->link);

	sec->next_a->next = nil;

	mem->head = sec;
	mem->tail = sec;
	mem->avlb = sec;

	return 0;
}

void
mem_destroy(Mem *mem)
{
	MemSec *a = mem->head;
	MemSec *b;

	while (a) {
		b = next_section(a);

		free(a);

		a = b;
	}

	mem->head = nil;
	mem->tail = nil;
	mem->avlb = nil;
}

void *
mem_next(Mem *mem, size_t size)
{
	MemSec *avlb = mem->avlb;
	BfrR *rdr = &avlb->rdr;

	if (bfrr_has(rdr, size)) {
		return bfrr_read(rdr, size);
	}

	int e = add_section(mem);

	err_ret(e, nil);

	return mem_next(mem, size);
}

static MemSec *
new_section(size_t size)
{
	size_t total = sizeof(MemSec) + size;
	MemSec *sec = malloc(total);

	nil_jmp(sec, end);

	bfr_init(&sec->bfr, size, sec + 1);
	bfrr_init(&sec->rdr, &sec->bfr);
end:
	return sec;
}

static int
add_section(Mem *mem)
{
	assert(mem->tail != nil);
	assert(mem->avlb != nil);

	MemSec *tail = mem->tail;
	size_t size = tail->bfr.size;
	MemSec *sec = new_section(size);
	MemSec *avlb = mem->avlb;

	dlink_set(&tail->link, &sec->link);

	if (bfrr_at_end(&avlb->rdr)) {
		avlb = next_avlb(avlb);

		mem->avlb = avlb;
	}

	if (avlb) {
		link_set(&avlb->next_a, &sec->next_a);

	} else {
		mem->avlb = sec;
	}
}

static MemSec *
next_section(MemSec *sec)
{
	DLink *next = sec->link.next;

	return container_of(next, MemSec, link);
}

/* static */
int
new_pool(size_t size)
{
	addr *pool = mem_alloc(OVERHEAD + size);
	Head *head = (Head *)(pool + 1);

	err_nil(pool, "new_pool(%ul) failed.", size);

	init_head(head, size);

	add_pool(pool);

	return 0;
error:
	return -1;
}

Node *
seek(size_t size)
{
	Node *node = nodes_rewind();
	size_t size_found = 0;

	while (node) {
		size_found = node->size;

		if (size_found == size) {
			return nodes_rmv();
		}

		if (size_found > size) {
			if (size_found > MIN_SIZE) {
				nodes_split(size);
			}

			return nodes_rmv();
		}

		node = nodes_next();
	}

	return nil;
}

Node *
expand(Node *node, size_t new_size)
{
	Node *next = nil;

	while (node->size < new_size) {
		next = successor_of(node);

		if (next) {
			node->size += next->size + sizeof(Node);

			nodes_rmv();

		} else {
			return nil;
		}
	}

	return node;
}

void *
relocate(Node *src_node, size_t new_size)
{
	Node *dst_node = seek(new_size);

	if (dst_node) {
		copy_to(dst_node, src_node);

		nodes_add(src_node);

		return ADDR_OF(dst_node);
	}

	return nil;
}

Node *
successor_of(Node *node)
{
	char *ptr = ADDR_OF(node);
	Node *target = (Node *)(ptr + node->size);
	Node *head = nodes_rewind();

	while (head) {
		if (head == target) {
			return head;
		}

		head = nodes_next();
	}

	return nil;
}

void
nodes_clr(void)
{
	nodes.first = nil;
	nodes.head = nil;
	nodes.prev = nil;
}

void
nodes_add(Node *node)
{
	addr_put(node, nodes);

	nodes = node;
}

Node *
nodes_rmv(void)
{
	Node *head = nodes.head;

	nodes.head = head->next;
	*nodes.prev = nodes.head;

	return head;
}

Node *
nodes_rewind(void)
{
	Node *node = nodes.first;

	nodes.head = node;
	nodes.prev = &node;

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
	size_t need = size + sizeof(Node);
	char *ptr = (char *)head + need;
	Node *new_node = (Node *)ptr;

	new_node->size = head->size - need;
	new_node->next = head->next;

	head->size = size;
	head->next = new_node;
}

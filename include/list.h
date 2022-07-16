#ifndef __LIST__
#define __LIST__

#include "common.h"

typedef struct node_d {
	char* ptr;
	struct node_d* prev;
	struct node_d* next;
} node_t;

typedef struct {
	unsigned int len;
	node_t* head;
} list_t;

/*
 * init procedure.
 */
void
list_init(list_t* l);

/*
 * free procedure.
 */
void
list_free(list_t* l);

/*
 * init with file path lines.
 */
ret_t
list_from_path(list_t* l, const char* p);

/*
 * append node with value val.
 */
void
list_add(list_t* l, char* val);

/*
 * get next node from list.
 */
node_t*
list_next(node_t* n);

#endif

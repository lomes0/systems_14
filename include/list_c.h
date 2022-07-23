#ifndef __LIST_C__
#define __LIST_C__

#include "common.h"

typedef struct node_d {
	char* ptr;
	struct node_d* next;
} node_t;

typedef struct {
	unsigned int len;
	node_t* head;
	node_t* last;
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
 * aapend value procedure.
 */
void
list_add(list_t* l, char* val);

/*
 * retrive next node procedure.
 */
node_t*
list_next(node_t* n);

/*
 * aligned print.
 */
void
list_print_pretty(list_t* l);

#endif

#ifndef __LIST__
#define __LIST__

#include "common.h"
#include "log.h"

typedef struct node_d {
	char* ptr;
	struct node_d* prev;
	struct node_d* next;
} node_t;

typedef struct {
	unsigned int len;
	node_t* head;
	node_t* last;
} list_t;

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

/*
 * init with file path lines.
 */
int
list_load_from_file(list_t* list, const char* p, log_t* l);

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

#endif /*__LIST__*/

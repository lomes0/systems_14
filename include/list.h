#ifndef __LIST__
#define __LIST__

#include "common.h"
#include "log.h"
#include "node.h"

typedef struct {
	unsigned int len;
	node_t* first;
	node_t* last;
} list_t;

/*
 * append node with value val.
 */
void
list_append(list_t* l, char* val);

/*
 * get next node from list.
 */
node_t*
list_next(node_t* n);

node_t*
list_get_head(list_t* list);

node_t*
list_get_last(list_t* list);

/*
 * init with file path lines.
 */
ret_t
list_from_file(list_t* list, const char* p, log_t* l);

/*
 * free procedure.
 */
void
list_free(list_t* l);

/*
 * init procedure.
 */
void
list_init(list_t* l);

#endif /*__LIST__*/

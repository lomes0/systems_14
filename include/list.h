#ifndef __LIST__
#define __LIST__

#include "common.h"
#include "log.h"
#include "node.h"

typedef struct {
	node_t* head;
	node_t* last;
	int len;
} list_t;

void
list_append(list_t* l, node_t* n);

void
list_replace(list_t* list, node_t* p, list_t* in);

node_t*
list_next(node_t* n);

//node_t*
//list_get_head(list_t* list);

//node_t*
//list_get_last(list_t* list);

ret_t
list_from_file(list_t* list, const char* p, log_t* l);

void
list_free(list_t* l);

void
list_init(list_t* l);

#endif /*__LIST__*/

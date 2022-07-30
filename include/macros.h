#ifndef __MACROS__
#define __MACROS__

#include "line.h"
#include "lines.h"
#include "btree.h"

typedef struct {
	btree_t* table;
} macros_t;

int macros_has(macros_t* m, line_t* head);

void macros_store(macros_t* m, line_t* head, lines_t* body);

lines_t* macros_body(macros_t* m, line_t* head);

#endif /* __MACROS__ */

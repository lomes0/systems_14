#ifndef __MACROS__
#define __MACROS__

#include "line.h"
#include "lines.h"
#include "btree.h"

typedef struct {
	btree_t* table;
} macros_t;

int macros_has(macros_t* m, str_t head_str);

void macros_store(macros_t* m, str_t head_str, lines_t* body);

lines_t* macros_body(macros_t* m, str_t head_str);

void macros_free(macros_t* m);

macros_t* macros_create();

#endif /* __MACROS__ */

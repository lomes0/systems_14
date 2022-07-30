#include <stdlib.h>

#include "macros.h"

int
macros_has(macros_t* m, str_t head_str)
{
	return btree_has(m->table, head_str);
}

lines_t*
macros_body(macros_t* m, str_t head_str)
{
	return (lines_t*) btree_get(m->table, head_str);
}

void
macros_store(macros_t* m, str_t head_str, lines_t* body)
{
	btree_insert(m->table, head_str, body);
}

void
macros_free(macros_t* m)
{

}

macros_t*
macros_create()
{
    return NULL;
}
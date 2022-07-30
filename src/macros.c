#include <stdlib.h>

#include "macros.h"

int
macros_has(macros_t* m, line_t* head)
{
	str_t word = line_word_i(head, 1);
	return btree_has(m->table, word);
}

lines_t*
macros_body(macros_t* m, line_t* head)
{
	str_t word = line_word_i(head, 1);
	return btree_get(m->table, word);
}

void
macros_store(macros_t* m, line_t* head, lines_t* body)
{
	str_t word = line_word_i(head, 1);
	btree_insert(m->table, word, body);
}

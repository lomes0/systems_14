#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include <string.h>

#include "list_c.h"
#include "scanner.h"
#include "common.h"

static void
list_clear(list_t* l)
{
	int i;
	node_t* node;
	node_t* curr;

	if (l->len == 0) {
		return;
	}

	node = l->head;

	for (i = 0; i < l->len - 1; ++i) {
		curr = node;
		node = list_next(node);

		free(curr->ptr);
		free(curr);
	}
	
	free(node->ptr);
	free(node);
	l->len = 0;
}

void
list_init(list_t* l)
{
	l->len = 0;
}

void
list_free(list_t* l)
{
	list_clear(l);
}

void
list_add(list_t* l, char* val)
{
	node_t* node = malloc(sizeof(node_t));
	node->ptr = val;
	node->next = NULL;

	switch (l->len)
	{
		case 0:
		{
			l->head = node;
			l->last = node;
			break;
		}
		default:
		{
			node_t* prev = l->last;
			l->last = node;
			prev->next = node;
			break;
		}
	}

	l->len++;
}

node_t*
list_head(list_t* l)
{
	return l->head;
}

node_t*
list_next(node_t* n)
{
	return n->next;
}

ret_t
list_from_path(list_t* l, const char* p)
{
	ret_t ret;
	scanner_t s;
	FILE* f;

	f = fopen(p, "r");
	scanner_init(&s, f);

	do {
		char* line;

		/*
		 * read next line from stream.
		 */
		ret = scanner_next_line(&s, &line);

		if (ret != RET_OK && ret != RET_EOF) {

			list_clear(l);
			scanner_free(&s);
			fclose(f);
			return ret;
		}

		/*
		 * append line to list.
		 */
		list_add(l, line);

	} while (ret != RET_EOF);

	scanner_free(&s);
	fclose(f);

	return RET_OK;
}

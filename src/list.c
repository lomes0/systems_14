#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include <string.h>

#include "include/list.h"
#include "include/scanner.h"
#include "include/common.h"

void
list_add(list_t* list, char* val)
{
	node_t* node = malloc(sizeof(node_t));
	node->ptr    = val;

	switch (list->len)
	{
		case 0:
		{
			list->head = node;
			list->last = node;
			list->head->prev = NULL;
			list->head->next = NULL;
			list->last->prev = NULL;
			list->last->next = NULL;
			break;
		}
		case 1:
		{
			l->last = node;
			l->last->next = NULL;
			l->last->prev = l->head;
			l->head->next = l->last;
		}
		default:
		{
			node_t* curr;
			curr = l->last;
			curr->next    = node;
			l->last       = node;
			l->last->prev = curr;
			l->last->next = NULL;
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
list_prev(node_t* n)
{
	return n->prev;
}

node_t*
list_next(node_t* n)
{
	return n->next;
}

int
list_load_from_file(list_t* list, const char* p, log_t* l)
{
	ret_t ret;
	scanner_t s;

	scanner_init(&s, p);

	do {
		char* line;

		/*
		 * read next line from stream.
		 */
		ret = scanner_next_line(&s, &line);

		if (ret != RET_OK && ret != RET_EOF) {
			list_clear(l);
			scanner_free(&s);
			//TODO::log err
			return -1;
		}

		/*
		 * append line to list.
		 */
		list_add(l, line);

	} while (ret != RET_EOF);

	scanner_free(&s);

	return 0;
}

void
list_free(list_t* list)
{
	int i;
	node_t* node;
	node_t* curr;

	if (list->len == 0) {
		return;
	}

	node = list->head;

	for (i = 0; i < list->len - 1; ++i) {
		curr = node;
		node = list_next(node);

		free(curr->ptr);
		free(curr);
	}
	
	free(node->ptr);
	free(node);
	list->len = 0;
}

void
list_init(list_t* l)
{
	l->len = 0;
}
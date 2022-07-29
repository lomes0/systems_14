#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include <string.h>

#include "list.h"
#include "scanner.h"
#include "common.h"

void
list_append(list_t* list, node_t* n)
{
	switch (list->len)
	{
		case 0:
		{
			list->head = n;
			list->last = n;
			list->head->prev = NULL;
			list->head->next = NULL;
			list->last->prev = NULL;
			list->last->next = NULL;
			break;
		}
		case 1:
		{
			list->last = n;
			list->last->next = NULL;
			list->last->prev = list->head;
			list->head->next = list->last;
		}
		default:
		{
			node_t* curr;
			curr = list->last;
			curr->next       = n;
			list->last       = n;
			list->last->prev = curr;
			list->last->next = NULL;
			break;
		}
	}

	list->len++;
}

void
list_replace(list_t* list, node_t* p, list_t* in)
{
	node_t* before = p->prev;
	node_t* after  = p->next;

	node_t* start  = in->head;
	node_t* end    = in->last;

	start->prev = before;
	end->next = after;

	if (before != NULL) {
		before->next = start;
	}

	if (after != NULL) {
		after->prev = end;
	}

	list->len += in->len;
}

void
list_append_val(list_t* list, void* ptr)
{
	node_t* n = malloc(sizeof(node_t));

	n->ptr = ptr;

	list_append(list, n);
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

ret_t
list_from_file(list_t* list, const char* p, log_t* l)
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
			list_free(list);
			scanner_free(&s);
			//TODO::log err
			return ret;
		}

		/*
		 * append line to list.
		 */
		list_append_val(list, line);

	} while (ret != RET_EOF);

	scanner_free(&s);

	return RET_OK;
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

#include <stdlib.h>
#include <alloca.h>

#include "list.h"
#include "scanner.h"
#include "str.h"
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
			list->head->prev = nullptr;
			list->head->next = nullptr;
			list->last->prev = nullptr;
			list->last->next = nullptr;
			break;
		}
		case 1:
		{
			list->last = n;
			list->last->next = nullptr;
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
			list->last->next = nullptr;
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

	if (before != nullptr) {
		before->next = start;
	}

	if (after != nullptr) {
		after->prev = end;
	}

	list->len += in->len;
}

void
list_append_val(list_t* list, void* ptr)
{
	node_t* n = (node_t*) malloc(sizeof(node_t));

	n->ptr = ptr;

	list_append(list, n);
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
    str_t str;

	scanner_init(&s, p, l);

	do {
		/*
		 * read next line from stream.
		 */
		ret = scanner_next_line(&s, &str, l);

		if (ret != RET_OK && ret != RET_EOF) {
			list_free(list);
			log_err(l, "%s", "scanner next line failure [ret=%d].", ret);
			goto out;
		}

		/*
		 * append line to list.
		 */
		list_append_val(list, str.c_str);

	} while (ret != RET_EOF);

out:
    scanner_free(&s);

	return ret;
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

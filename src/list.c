#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include <string.h>

#include "list.h"
#include "scanner.h"
#include "common.h"

static void
list_free(list_t* l)
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
list_add(list_t* l, char* val)
{
	node_t* node = malloc(sizeof(node_t));
	node->ptr    = str_cpy(val);

	switch (l->len)
	{
		case 0:
		{
			l->head = node;
			l->last = node;
			l->head->prev = NULL;
			l->head->next = NULL;
			l->last->prev = NULL;
			l->last->next = NULL;
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
	assert(n->prev != NULL);
	return n->prev;
}

node_t*
list_next(node_t* n)
{
	assert(n->next != NULL);
	return n->next;
}

ret_t
list_from_path(list_t* l, const char* p)
{
	FILE* f = fopen(p, "r");
	scanner_t s;

	scanner_init(&s, f);

	do {
		ret_t ret;
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

//#define ASCII_SPACE_VAL	   (' ')
//#define ASCII_TAB_VAL	   ('	')
//#define TAB_MAX_SIZE       (0x4)
//#define LINE_CHARS_WIDTH   (0x20)
//#define LINE_PREFIX_WIDTH  (LINE_CHARS_WIDTH + (TAB_MAX_SIZE * 2))
//
//static void
//print_tab_align(int *pos)
//{
//	const int pos_mod = *pos % TAB_MAX_SIZE;
//	const char* space_a = " ";
//	const char* space_b = "  ";
//	const char* space_c = "   ";
//	const char* space_d = "    ";
//	const char* tab_str;
//
//	switch (pos_mod)
//	{
//		case 0: tab_str = space_d; *pos += 4; break;
//		case 1: tab_str = space_c; *pos += 3; break;
//		case 2: tab_str = space_b; *pos += 2; break;
//		case 3: tab_str = space_a; *pos += 1; break;
//	}
//
//	printf("%s", tab_str);
//}
//
//static void
//print_padding(int pos)
//{
//	const int num_spaces = LINE_PREFIX_WIDTH - pos;
//	char* spaces;
//
//	spaces = alloca((num_spaces + 1) * sizeof(char));
//	memset(spaces, ASCII_SPACE_VAL, num_spaces);
//	spaces[num_spaces] = '\0';
//
//	printf("%s|\n", spaces);
//}
//
//static void
//print_line(const char* str, int idx)
//{
//	int pos = 0;
//	const char* c = str;
//
//	/*
//	 * print current line.
//	 */
//	while (*c != '\0') {
//
//		/*
//		 * enforce line width.
//		 */
//		if (pos >= LINE_CHARS_WIDTH) {
//			print_padding(pos);
//			pos = 0;
//			c++;
//			continue;
//		}
//
//		/*
//		 * handle tab case.
//		 */
//		if (*c == ASCII_TAB_VAL) {
//			print_tab_align(&pos);
//			c++;
//			continue;
//		}
//
//		printf("%c", *c);
//		pos++;
//		c++;
//	}
//
//	print_padding(pos);
//}
//
//void
//list_print_pretty(list_t* l)
//{
//	node_t* node = l->head;
//	int idx;
//
//	if (l->len == 0) {
//		return;
//	}
//
//	idx = 0;
//	print_line(node->ptr, idx++);
//
//	while(node->next != NULL)
//	{
//		node = list_next(node);
//		print_line(node->ptr, idx++);
//	}
//}

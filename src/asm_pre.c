#include <stdlib.h>

#include "asm_pre.h"
#include "list.h"
#include "log.h"
#include "strings.h"

#define list_foreach(list, n, type, val) \
	for (n = list->head, val = (type)n->ptr; n->next != NULL; n = n->next)

static void
asm_pre_expend_macro(asm_pre_t* a, line_t* head)
{
	line_t* line;
	lines_t* body = macros_body(&a->macros, head);
	
	for (line = lines_first(body); line != NULL; line = line->next) {
		lines_append(&a->lines_out, line_copy(line));
	}
}

static int
asm_pre_known_macro(asm_pre_t* a, line_t* head)
{
	if (!line_is_single_word(head)) {
		return 0;
	}

	return macros_has(&a->macros, head);
}

static line_t*
asm_pre_try_store_macro(asm_pre_t* a, line_t* head, log_t* l)
{
	const char* macro_name;
	lines_t* body = malloc(sizeof(lines_t));
	line_t* next = head->next;
	line_t* curr;

	macro_name = line_word_i(head, 1);
	lines_init(body);

	/* forbid repeating macros. */
	if (asm_pre_known_macro(a, head)) {
		lines_free(body);
		log_err(l, "macro double defenition [macro=%s]", macro_name);
		return NULL;
	}

	while (next != NULL) {
		curr = next;

		/* forbid nested macros. */
		if (line_is_macro_def(curr)) {
			log_err(l, "macro nested macro defenition [macro=%s]", macro_name);
			lines_free(body);
			return NULL;
		}

		if (line_is_macro_end(curr)) {
			macros_store(&a->macros, head, body);
			return curr;
		}

		next = curr->next;
		lines_append(body, curr);
	}

	lines_free(body);
	log_err(l, "macro missing end statement [macro=%s]", macro_name);

	return NULL;
}

void
asm_pre_sheldi(asm_pre_t* a, log_t* l)
{
	line_t* line;
	lines_t* out = &a->lines_out;
	line_t* next = lines_first(&a->lines);

	while (next != NULL) {
		line = next;
		
		/* a known macro usage? */
		if (asm_pre_known_macro(a, line)) {
			asm_pre_expend_macro(a, line);
			continue;
		}

		/* a new macro defenition? */
		if (line_is_macro_def(line)) {
			line = asm_pre_try_store_macro(a, line, l);
			continue;
		}

		next = line->next;
		lines_append(out, line);
	}
}

static line_t*
asm_pre_create_line(asm_pre_t* a, const char* line_c, log_t* l)
{
	int seg_num;
	char (*segments)[LINE_SEG_MAX] = {0};
	char delims[3];

	delims[0] = CHAR_SPACE;
	delims[1] = CHAR_TAB;
	delims[3] = CHAR_COMMA;
	delims[4] = CHAR_NULL;

	seg_num = strings_break_by((char**)segments, LINE_SEG_MAX, line_c, delims);

	return line_create((char**)segments, seg_num);
}

static void
asm_pre_init_lines(asm_pre_t* a, list_t* lines_c, log_t* l)
{
	const char* line_c; node_t* n;

	lines_init(&a->lines);

	list_foreach(lines_c, n, const char*, line_c) {

		line_t* line = asm_pre_create_line(a, line_c, l);

		if (line_is_white(line) ||
		    line_is_cmt(line)) {

			line_free(line);
			continue;
		}

		lines_append(&a->lines, line);
	}
}

int
asm_pre_init(asm_pre_t* a, const char* p, log_t* l)
{
	list_t lines_c;

	list_init(&lines_c);

	if (list_from_file(&lines_c, p, l) != RET_OK) {
		return -1;
	}

	asm_pre_init_lines(a, &lines_c, l);

	return 0;
}

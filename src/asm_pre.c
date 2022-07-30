#include <stdlib.h>

#include "asm_pre.h"
#include "strings.h"
#include "list.h"
#include "log.h"

static void
asm_pre_expend_macro(asm_pre_t* a, line_t* head)
{
	line_t* line;
	lines_t* body = macros_body(a->macros, head);
	
	for (line = lines_first(body); line != NULL; line = line->next) {
		lines_append(a->lines_out, line_copy(line));
	}
}

static int
asm_pre_known_macro(asm_pre_t* a, line_t* head)
{
	if (!line_is_single_word(head)) {
		return 0;
	}

	return macros_has(a->macros, head);
}

static line_t*
asm_pre_try_store_macro(asm_pre_t* a, line_t* head, log_t* l)
{
	lines_t* body = lines_create();
	line_t* next = head->next;
	line_t* curr;

	str_t head_str = line_word_i(head, 1);
	lines_init(body);

	/* forbid repeating macros. */
	if (asm_pre_known_macro(a, head)) {
		lines_free(body);
		log_err(l, "macro double defenition [macro=%s]", head_str.c_str);
		return NULL;
	}

	while (next != NULL) {
		curr = next;

		/* forbid nested macros. */
		if (line_is_macro_def(curr)) {
			log_err(l, "macro nested macro defenition [macro=%s]", head_str.c_str);
			lines_free(body);
			return NULL;
		}

		if (line_is_macro_end(curr)) {
			macros_store(a->macros, head, body);
			return curr;
		}

		next = curr->next;
		lines_append(body, curr);
	}

	lines_free(body);
	log_err(l, "macro missing end statement [macro=%s]", head_str.c_str);

	return NULL;
}

void
asm_pre_sheldi(asm_pre_t* a, log_t* l)
{
	line_t* line;
	line_t* next = lines_first(a->lines);

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
		lines_append(a->lines_out, line);
	}
}

static line_t*
asm_pre_create_line(asm_pre_t* a, const char* line_c, log_t* l)
{
	char delims[3];
	str_t* strs;
	int seg_num;

	delims[0] = CHAR_SPACE;
	delims[1] = CHAR_TAB;
	delims[2] = CHAR_NULL;

	seg_num = str_split(&strs, line_c, delims);

	return line_create(strs, seg_num);
}

static void
asm_pre_prepare_lines(asm_pre_t* a, list_t* lines_c, log_t* l)
{
	const char* line_c; node_t* n;

	a->lines = lines_create();
	a->lines_out = lines_create();

	list_foreach(lines_c, n, const char*, line_c) {

		line_t* line = asm_pre_create_line(a, line_c, l);

		if (line_is_white(line) ||
		    line_is_cmt(line)) {

			line_free(line);
			continue;
		}

		lines_append(a->lines, line);
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

	asm_pre_prepare_lines(a, &lines_c, l);

	return 0;
}

void
asm_pre_free(asm_pre_t* a)
{
	//lines
	//lines_out
	//macros
}

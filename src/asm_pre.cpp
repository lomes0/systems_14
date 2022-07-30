#include <stdlib.h>

#include "asm_pre.h"
#include "strings.h"
#include "list.h"
#include "log.h"

static void
asm_pre_expend_macro(asm_pre_t* a, line_t* head)
{
	line_t* line;
	lines_t* body = macros_body(a->macros, line_word_i(head, 0));
	
	for (line = lines_first(body); line != nullptr; line = line->next) {
		lines_append(a->lines_out, line_copy(line));
	}
}

static line_t*
asm_pre_try_store_macro(asm_pre_t* a, line_t* head, log_t* l)
{
	lines_t* body = lines_create();
	line_t* next = head->next;
	line_t* curr;

	str_t head_str = line_word_i(head, 1);

	/* forbid multiple macro definitions. */
	if (macros_has(a->macros, head_str)) {
		lines_free(body);
		log_err(l, "macro double definition [macro=%s]", head_str.c_str);
		return nullptr;
	}

	while (next != nullptr) {
		curr = next;

		/* forbid nested macros. */
		if (line_is_macro_def(curr)) {
			log_err(l, "macro nested macro definition [macro=%s]", head_str.c_str);
			lines_free(body);
			return nullptr;
		}

		if (line_is_macro_end(curr)) {
			macros_store(a->macros, head_str, body);
			return curr;
		}

		next = curr->next;
		lines_append(body, curr);
	}

	lines_free(body);
	log_err(l, "macro missing end statement [macro=%s]", head_str.c_str);

	return nullptr;
}

void
asm_pre_sheldi(asm_pre_t* a, log_t* l)
{
	line_t* line;
	line_t* next = lines_first(a->lines);

	while (next != nullptr) {
		line = next;
		
		/* a known macro usage? */
		if (line_is_single_word(line)) {
            if (macros_has(a->macros, line_word_i(line, 0))) {
                asm_pre_expend_macro(a, line);
                next = line->next;
                continue;
            }
		}
		/* a new macro definition? */
		if (line_is_macro_def(line)) {
			line = asm_pre_try_store_macro(a, line, l);
            next = line->next;
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
	const char* line_c; node_t* lin_n;

    for (lin_n = lines_c->head;  lin_n->next != nullptr; lin_n = lin_n->next) {
        line_c = (char*) lin_n->ptr;

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

    a->lines = lines_create();
    a->lines_out = lines_create();
    a->macros = macros_create();

	if (list_from_file(&lines_c, p, l) != RET_EOF) {
		return -1;
	}

	asm_pre_prepare_lines(a, &lines_c, l);

	return 0;
}

void
asm_pre_free(asm_pre_t* a)
{
    lines_free(a->lines);
    lines_free(a->lines_out);
    macros_free(a->macros);
}

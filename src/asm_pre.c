#include <stdlib.h>

#include "asm_pre.h"
#include "scanner.h"
#include "list.h"
#include "log.h"
#include "strings.h"

#define MACRO_STR "macro"

#define asm_pre_foreach(lines, n) \
	for (n = list_get_head(lines); n != list_get_last(lines); list_next(n))

#define list_foreach(list, n, type, val) \
	for (n = list->head, val = (type)n->ptr; n->next != NULL; n = n->next)

	//     - properly parse lines.
	//       - create a list of parsed lines.
	//             - add a functionaly: parsed line 2 raw line


//static char*
//asm_pre_test_macro_def(const char* line, log_t* l)
//{
//	if (!string_has_prefix(line, MACRO_STR)) {
//		return NULL;
//	}
//
//	//if (string_p
//
//	return NULL;
//}

static line_t*
asm_pre_try_store_macro(asm_pre_t* a, line_t* line, log_t* l)
{
	//TODO: the only fatal is a nested macro.
	return NULL;
}

//static void
//asm_pre_try_store_macro(asm_pre_t* a, char* macro, char* macro_body)
//{
//}
//
//void
//asm_pre_store_macros(asm_pre_t* a, log_t* l)
//{
//}
//
//void
//asm_pre_expend_macros(asm_pre_t* asm_pre, log_t* l)
//{
//}
//
//void
//asm_pre_write_file(asm_pre_t* asm_pre, log_t* l)
//{
//}

static lines_t*
asm_pre_macro_get_body(asm_pre_t* a, line_t* name)
{
	return NULL;
}

static line_t*
asm_pre_replace_macro(asm_pre_t* a, line_t* name)
{
	/*TODO:: log err if macro is not exists..*/
	lines_t* body = asm_pre_macro_get_body(a, name);

	lines_replace(name, body->first, body->last);

	free(name);

	return body->last;
}

static int
asm_pre_has_macro(asm_pre_t* a, const char* word)
{
	/* TODO::IMPL */
	return 0;
}

static int
asm_pre_known_macro(asm_pre_t* a, line_t* line)
{
	const char* word;

	if (!line_is_single_word(line)) {
		return 0;
	}

	word = line_get_word_i(line, 0);

	return asm_pre_has_macro(a, word);
}

void
asm_pre_sheldi(asm_pre_t* a, log_t* l)
{
	line_t* line = lines_first(&a->lines);

	for (; line->next != NULL; line = line->next) {
		
		/* a known macro usage? */
		if (asm_pre_known_macro(a, line)) {
			line = asm_pre_replace_macro(a, line);
			continue;
		}

		/* a new macro defenition? */
		if (line_is_macro_def(line)) {
			line = asm_pre_try_store_macro(a, line, l);
			continue;
		}
	}
}

	// pre-assembler
	//  - macro table: macro name, a list of line_t, composing the macro.

static line_t*
asm_pre_parse_line(asm_pre_t* a, const char* line_c, log_t* l)
{
	char (*segments)[LINE_SEG_MAX];

	strings_break_by_whites((char**)segments, LINE_SEG_MAX, line_c);

	return lines_create_line(segments);
}

static void
asm_pre_init_lines(asm_pre_t* a, list_t* lines_c, log_t* l)
{
	const char* line_c; node_t* n;

	lines_init(&a->lines);

	list_foreach(lines_c, n, (const char*), line_c) {

		line_t* line = asm_pre_parse_line(a, line_c, l);

		if (line_is_white(line) ||
		    line_is_cmt(line)) {

			free(line);
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

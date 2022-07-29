#include <stdlib.h>

#include "lines.h"

line_t*
line_create(char (*segments)[LINE_SEG_MAX])
{
	//i = 0;
	//while ((seg = segments[i++]) != NULL) {
	//	// get parse the token
	//}

	return NULL;
}

int
line_is_white(line_t* line)
{
	return 0;
}

int
line_is_cmt(line_t* line)
{
	return 0;
}

int
line_is_macro_def(line_t* line)
{
	return 0;
}

int
line_is_single_word(line_t* line)
{
	return 0;
}

const char*
line_get_word_i(line_t* line, int i)
{
	return NULL;
}






void
lines_replace(lines_t* lines, line_t* p, lines_t* in)
{
	list_replace(lines, p, in);
}

line_t*
lines_first(lines_t* lines)
{
	return lines->head;
}

void lines_append(lines_t* lines, line_t* line)
{
	list_append(lines, line);
}

void lines_init(lines_t* lines)
{
	list_init(lines);
}

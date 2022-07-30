#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "line.h"
#include "stdio.h"

#define line_data(line, type) ((type) line->ptr);

int
line_is_white(line_t* line)
{
	line_seg_t* line_s = line_data(line, line_seg_t*);

	return line_s->size == 0;
}

int
line_is_cmt(line_t* line)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);

	str_t word_0 = line_s->strs[0];

	return line_s->size == 1 && strcmp(word_0.c_str, ";") == 0;
}

static int
alpha_str(const char* word)
{
	while (*word != '\0') {
		if (!isalnum(*word++)) {
			return 0;
		}
	}

	return 1;
}

int
line_is_macro_def(line_t* line)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);

	str_t word_0 = line_s->strs[0];
	str_t word_1 = line_s->strs[1];

	return line_s->size == 2 && strcmp(word_0.c_str, "macro") == 0 && alpha_str(word_1.c_str);
}

int
line_is_macro_end(line_t* line)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);

	str_t word_0 = line_s->strs[0];

	return line_s->size == 1 && strcmp(word_0.c_str, "endmacro") == 0;
}

int
line_is_single_word(line_t* line)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);
	
	return line_s->size == 1;
}

str_t
line_word_i(line_t* line, int i)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);

	return line_s->strs[i];
}

line_t*
line_copy(line_t* line)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);
	
	return line_create(line_s->strs, line_s->size);
}

line_t*
line_create(str_t* strs, int size)
{
	line_t* line = (line_t*) malloc(sizeof(line_t));
	line_seg_t* data = (line_seg_t*) malloc(sizeof(line_seg_t));

	data->strs = strs;
	data->size = size;
    line->ptr = data;

	return line;
}

void
line_free(line_t* line)
{
    line_seg_t* line_s = line_data(line, line_seg_t*);

	free(line_s);
	free(line);
}

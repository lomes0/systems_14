#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lines.h"

line_t*
line_create(char** segs, int seg_num)
{
	line_t* line = malloc(sizeof(line_t));

	line_data_t* data = malloc(sizeof(line_data_t));

	int i = 0;

	while (i < seg_num) {
		data->segs[i] = segs[i];
		i++;
	}

	data->seg_num = seg_num;

	line->ptr = data;

	return line;
}

int
line_is_white(line_t* line)
{
	line_data_t* data = line->ptr;

	return data->seg_num == 0;
}

int
line_is_cmt(line_t* line)
{
	line_data_t* data = line->ptr;

	char* word_0 = data->segs[0];

	return data->seg_num == 1 && strcmp(word_0, ";") == 0;
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
	line_data_t* data = line->ptr;

	char* word_0 = data->segs[0];
	char* word_1 = data->segs[1];

	return data->seg_num == 2 && strcmp(word_0, "macro") == 0 && alpha_str(word_1);
}

int
line_is_single_word(line_t* line)
{
	line_data_t* data = line->ptr;
	
	return data->seg_num == 1;
}

const char*
line_word_i(line_t* line, int i)
{
	line_data_t* data = line->ptr;

	return data->segs[i];
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

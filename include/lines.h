#ifndef __LINES__
#define __LINES__

#include "list.h"

#define LINE_SEG_MAX (5)

typedef list_t lines_t;

typedef node_t line_t;

typedef struct {
	//metadata (type of line
	//label
	char** segs;
	int seg_num;
} line_data_t;

int line_is_white(line_t* line);

int line_is_cmt(line_t* line);

int line_is_macro_def(line_t* line);

int line_is_macro_end(line_t* line);

int line_is_single_word(line_t* line);

const char* line_word_i(line_t* line, int i);
	
line_t* line_create(char** segs, int seg_num);

line_t* line_copy(line_t* orig);

void line_free(line_t* line);



void lines_replace(lines_t* lines, line_t* p, lines_t* in);

line_t* lines_first(lines_t* lines);

void lines_append(lines_t* lines, line_t* line);

void lines_free(lines_t* lines);

void lines_init(lines_t* lines);

#endif //__LINES__

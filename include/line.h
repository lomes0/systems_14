#ifndef __LINEH__
#define __LINEH__

#include "node.h"
#include "str.h"

#define LINE_SEG_MAX (5)

typedef node_t line_t;

typedef struct {
	str_t* strs;
	int size;
} line_seg_t;

int line_is_white(line_t* line);

int line_is_cmt(line_t* line);

int line_is_macro_def(line_t* line);

int line_is_macro_end(line_t* line);

int line_is_single_word(line_t* line);

str_t line_word_i(line_t* line, int i);
	
line_t* line_copy(line_t* line);

line_t* line_create(str_t* strs, int size);

void line_free(line_t* line);

#endif /* __LINEH__ */

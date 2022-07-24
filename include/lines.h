#ifndef __LINES__
#define __LINES__

#include "list.h"

#define LINE_SEG_MAX (5)

typedef list_t lines_t;

typedef node_t line_t;

typedef struct {
	//metadata (type of line
	//label
	//data segments[]
	//int num_segments;
} line_data_t;

void lines_init(lines_t* lines);

void lines_append(lines_t* lines, line_t* line);

int line_is_white(line_t* line);

int line_is_cmt(line_t* line);

	//i = 0;
	//while ((seg = segments[i++]) != NULL) {
	//	// get parse the token
	//}
line_t* lines_create_line(char (*segments)[LINE_SEG_MAX]);

line_t* lines_first(lines_t* lines);

int line_is_macro_def(line_t* line);

void lines_replace(line_t* pos, line_t* start, line_t* end);

int line_is_single_word(line_t* line);

const char* line_get_word_i(line_t* line, int i);
	
#endif //__LINES__

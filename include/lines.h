#ifndef __LINES__
#define __LINES__

#include "list.h"
#include "line.h"

typedef list_t lines_t;

void lines_replace(lines_t* lines, line_t* p, lines_t* in);

line_t* lines_first(lines_t* lines);

void lines_append(lines_t* lines, line_t* line);

void lines_init(lines_t* lines);

lines_t* lines_create();

void lines_free(lines_t* lines);

#endif /* __LINES__ */

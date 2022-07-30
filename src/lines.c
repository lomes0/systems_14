#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lines.h"

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

void
lines_append(lines_t* lines, line_t* line)
{
	list_append(lines, line);
}

void
lines_init(lines_t* lines)
{
	list_init(lines);
}

lines_t*
lines_create()
{
	lines_t* lines = malloc(sizeof(lines_t));
	lines_init(lines);

	return lines;
}

void
lines_free(lines_t* lines)
{
	free(lines);
}

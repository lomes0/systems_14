#include <string.h>
#include <alloca.h>
#include <stdlib.h>

#include "str.h"

int
str_split(str_t** segs_p, const char* line_c, char* delims)
{
	str_t* segs = *segs_p;
	char* cp; int si;
	segs = NULL;

	str_t line_d;
	str_init_val(&line_d, line_c);

	si = 0;
	cp = strtok(line_d.c_str, delims);
	while (cp != NULL) {

		segs = realloc(segs, sizeof(str_t) * (si + 1));

		str_init_val(&segs[si], cp);

		cp = strtok(NULL, delims);

		si++;
	}

	return si;
}

void
str_init_val(str_t* str, const char* c_str)
{
	str->c_str = malloc((strlen(c_str) + 1) * sizeof(char));
	memcpy(str->c_str, c_str, (strlen(c_str) + 1) * sizeof(char));
}

void
str_free(str_t* str)
{
	free(str->c_str);
}

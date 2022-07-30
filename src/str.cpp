#include <string.h>
#include <alloca.h>
#include <stdlib.h>

#include "str.h"

int
str_split(str_t** strs_p, const char* line_c, char* delims)
{
	char* cp; int si;
	*strs_p = NULL;

	str_t line_d;
	str_init_val(&line_d, line_c);

	si = 0;
	cp = strtok(line_d.c_str, delims);
	while (cp != NULL) {

		*strs_p = (str_t*) realloc(*strs_p, sizeof(str_t) * (si + 1));

		str_init_val(&(*strs_p)[si], cp);

		cp = strtok(NULL, delims);

		si++;
	}

	return si;
}

void
str_init_val(str_t* str, const char* c_str)
{
	str->c_str = (char*) malloc((strlen(c_str) + 1) * sizeof(char));
	memcpy(str->c_str, c_str, (strlen(c_str) + 1) * sizeof(char));
}

void
str_free(str_t* str)
{
	free(str->c_str);
}

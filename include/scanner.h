#ifndef __SCANNER__
#define __SCANNER__

#include <stdio.h>
#include <sys/types.h>

#include "common.h"

typedef struct {

	FILE* file;
	char* buffer;
	u_int32_t bytes_size;
	u_int32_t bytes_free;
} scanner_t;

/*
 * Simple init procedure.
 */
void scanner_init(scanner_t* scanner, const char* p);

/*
 * Simple free procedure.
 */
void scanner_free(scanner_t* scanner);

/*
 * Load next line from file.
 */
ret_t scanner_next_line(scanner_t* scanner, char** line_ptr);

#endif /* __SCANNER__ */

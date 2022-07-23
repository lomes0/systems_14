#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "common.h"
#include "scanner.h"

static size_t bytes_block_size = 0x40;

static ret_t
scanner_alloc(scanner_t* scanner)
{
	size_t bytes_size = scanner->bytes_size;
	void** buffer_p   = (void**)&scanner->buffer;

	*buffer_p = realloc(*buffer_p, bytes_size +
	                               bytes_block_size);

	if (*buffer_p == NULL) {

		fprintf(stderr, "realloc failed.");
		return RET_MEM_FAULT;
	}

	scanner->bytes_free = bytes_block_size;

	return RET_OK;
}

static size_t
scanner_read_k(FILE* file, char* buffer, size_t bytes_max)
{
	size_t byte_i = 0;
	char c;

	do {
		if (byte_i == bytes_max) {
			return byte_i;
		}

		if ((c = fgetc(file)) == EOF) {
			return byte_i;
		}

		*(buffer + byte_i) = c;
		byte_i += sizeof(char);

	} while(1);

	return byte_i;
}

static int
scanner_read(scanner_t* s, int max)
{
	char* next_char_p = ((char*)s->buffer) + s->bytes_size;

	size_t bytes_red = scanner_read_k(s->file, next_char_p, max);

	s->bytes_size += bytes_red;
	s->bytes_free -= bytes_red;

	return bytes_red;
}

static int
scanner_read_char(scanner_t* s)
{
	return scanner_read(s, 1);
}

ret_t
scanner_next_line(scanner_t* s, char** line_ptr)
{
	ret_t ret;

	*line_ptr = NULL;
	s->bytes_free += s->bytes_size;
	s->bytes_size  = 0;

	/*
	 * Skip finished files.
	 */
	if (feof(s->file)) {
		return RET_EOF;
	}

	do {
		/*
		 * Prepare memory for the read.
		 */
		if ((ret = scanner_alloc(s)) != RET_OK) {
			return ret;
		}

		/*
		 * Reading char by char, for the sake of simplicty.
		 * We will exit upon:
		 *  - new line char.
		 *  - eof ~ zero bytes read.
		 */
		if (scanner_read_char(s) == 0) {
			s->buffer[s->bytes_size++] = '\0';
			break;
		}

		if (s->buffer[s->bytes_size - 1] == '\n') {
			s->buffer[s->bytes_size - 1] = '\0';
			break;
		}

	} while (1);

	/**len = scanner->bytes_size - 1;*/
	*line_ptr = s->buffer;
	*line_ptr = malloc(s->bytes_size * sizeof(char));
	memcpy((void*)*line_ptr, (void*)s->buffer, s->bytes_size);

	if (feof(s->file)) {
		return RET_EOF;
	}

	return RET_OK;
}

void
scanner_init(scanner_t* s, const char* p)
{
	//TODO:: try load path
	s->bytes_size = 0;
	s->bytes_free = 0;
	s->file       = NULL;
	s->buffer     = NULL;
}

void
scanner_free(scanner_t* s)
{
	free(s->buffer);
}

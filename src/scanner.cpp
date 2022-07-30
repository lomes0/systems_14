#include <stdlib.h>
#include <strings.h>

#include "scanner.h"
#include "common.h"

static size_t bytes_block_size = 0x40;

static ret_t
scanner_alloc(scanner_t* scanner, log_t* l)
{
	size_t bytes_size = scanner->bytes_size;

    scanner->buffer = (char*)realloc(scanner->buffer, bytes_size + bytes_block_size);

	if (scanner->buffer == nullptr) {
		log_err(l, "scanner alloc failure.");
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

static size_t
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
scanner_next_line(scanner_t* s, str_t* str_p, log_t* l)
{
	ret_t ret;

    str_p->c_str = nullptr;
	s->bytes_free = s->bytes_size;
	s->bytes_size = 0;

    /* skip readen files. */
	if (feof(s->file)) {
		return RET_EOF;
	}

	do {
		/*
		 * Prepare memory.
		 */
		if ((ret = scanner_alloc(s, l)) != RET_OK) {
			return ret;
		}

		/*
		 * Reading char by char, for the sake of simplicity.
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

    str_init_val(str_p, s->buffer);

    return feof(s->file) ? RET_EOF : RET_OK;
}

static FILE*
load_path(const char* p, log_t* l)
{
    FILE* f = fopen(p, "r");

    //TODO::make sure not dir
    //TODO::make sure not link

    if (!f) {
        log_err(l, "failed to read file [p=%s]", p);
    }

    return f;
}

void
scanner_init(scanner_t* s, const char* p, log_t* l)
{
	s->bytes_size = 0;
	s->bytes_free = 0;
	s->file       = load_path(p, l);
	s->buffer     = nullptr;
}

void
scanner_free(scanner_t* s)
{
	free(s->buffer);
}

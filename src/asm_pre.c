#include "asm_pre.h"
#include "scanner.h"
#include "list.h"
#include "log.h"

static int
asm_pre_load_source(asm_pre_t* asm_pre, log_t* l)
{
	const char* path = asm_pre_get_path(asm_pre);
	list_t* list = asm_pre_get_list(asm_pre);
	scanner_t s;
	ret_t ret;

	scanner_init(&s, path, l);

	do {
		char* line;

		/*
		 * read next line from stream.
		 */
		ret = scanner_next_line(&s, &line);

		if (ret != RET_OK && ret != RET_EOF) {
			list_free(list);
			scanner_free(&s);
			return ret;
		}

		/*
		 * append line to list.
		 */
		list_add(list, line);

	} while (ret != RET_EOF);

	scanner_free(&s);

	return RET_OK;
}

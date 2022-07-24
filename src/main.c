#include <stdlib.h>

#include "log.h"
#include "asm_runner.h"

int
main(int argc, const char** argv)
{
	log_t l; int ret;

	log_init(&l);

	asm_runner(argv + 1, argc - 1, &l);

	ret = log_has_fatal(&l) ? EXIT_FAILURE : EXIT_SUCCESS;

	log_flush(&l);

	return ret;
}




















//static int
//asm_pre_load_source(asm_pre_t* asm_pre, log_t* l)
//{
//	const char* path = asm_pre_get_path(asm_pre);
//	list_t* list = asm_pre_get_list(asm_pre);
//	scanner_t s;
//	ret_t ret;
//
//	scanner_init(&s, path, l);
//
//	do {
//		char* line;
//
//		/*
//		 * read next line from stream.
//		 */
//		ret = scanner_next_line(&s, &line);
//
//		if (ret != RET_OK && ret != RET_EOF) {
//			list_free(list);
//			scanner_free(&s);
//			return ret;
//		}
//
//		/*
//		 * append line to list.
//		 */
//		list_add(list, line);
//
//	} while (ret != RET_EOF);
//
//	scanner_free(&s);
//
//	return RET_OK;
//}
//


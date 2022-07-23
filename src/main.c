#include <stdlib.h>
#include "log.h"
#include "asm_runner.h"

int
main(int argc, const char** argv)
{
	int ret;
	log_t l;
	log_init(&l);

	asm_runner(argc - 1, argv + 1, &l);

	ret = log_has_fatal(&l) ? EXIT_FAILURE : EXIT_SUCCESS;

	log_flush(&l);

	return ret;
}

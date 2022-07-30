#include <stdlib.h>

#include "log.h"
#include "asm_runner.h"

int
main(int argc, const char* argv[])
{
    log_t l; int ret;

    log_init(&l);

    asm_runner(argv + 1, argc - 1, &l);

    ret = log_has_errs(&l) ? EXIT_FAILURE : EXIT_SUCCESS;

    log_flush(&l);

    return ret;
}

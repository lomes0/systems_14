#include <alloca.h>

#include "asm.h"
#include "asm_pre.h"
#include "list.h"
#include "scanner.h"

static int
asm_runner_asm(asm_pre_t* asm_pre, log_t* l)
{
	asm_t a;

	asm_parse_lines(&a, l);

	/* storing labels to symbol tables. */
	asm_store_labels(&a, l);

	return 0;
}

static int
asm_runner_pre_asm(asm_pre_t* asm_pre, log_t* l)
{
	asm_pre_save_macros(asm_pre, l);

	asm_pre_expend_macros(asm_pre, l);

	asm_pre_write_file(asm_pre, l);

	return 0;
}

int
asm_runner(int argc, const char** argv, log_t* l)
{
	int i;
	asm_pre_t* asm_pre = alloca(sizeof(asm_pre_t) * argc);

	/*
	 * Run pre-assembler.
	 */
	for (i = 0; i < argc; ++i) {
		asm_pre_init(asm_pre + i, *(argv + i), l);

		/*
		 * No point to move ahead on fatal errors (e.g file is unreadable).
		 */
		if (log_has_fatal(l)) {
			return -1;
		}

		asm_runner_pre_asm(asm_pre + i, l);

		/*
		 * No point to move ahead on fatal errors (e.g failure to expend macros).
		 */
		if (log_has_fatal(l)) {
			return -1;
		}
	}

	/*
	 * Run assembler.
	 */
	for (i = 0; i < argc; ++i) {
		asm_runner_asm(asm_pre + i, l);
	
		if (log_has_fatal(l)) {
			return -1;
		}
	}

	return 0;
}

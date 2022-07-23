#include <alloca.h>

#include "include/asm.h"
#include "include/asm_pre.h"
#include "include/list.h"
#include "include/scanner.h"

static int
asm_sh_asm(asm_t* a, log_t* l)
{
	asm_parse_lines(a, l);

	/* storing labels to symbol tables. */
	asm_store_labels(a, l);
}

static int
asm_sh_pre_asm(asm_pre_t* asm_pre, const char* p, log_t* l)
{
	asm_load_source(asm_pre, p, l);

	asm_store_macros(asm_pre, p, l);

	asm_expend_macros(asm_pre, p, l);

	asm_write_file(asm_pre, l);
}

int
asm_sh(int argc, const char** argv, log_t* l)
{
	asm_pre_t* asm_pre = alloca(sizeof(asm_pre_t));

	/*
	 * Run pre-assembler.
	 */
	for (i = 0; i < argc; ++i) {
		asm_pre_init(asm_pre + i, l);

		/*
		 * No point to move ahead on fatal errors (e.g input is unreadable).
		 */
		if (log_has_fatal(l)) {
			return -1;
		}

		asm_runner_pre_asm(asm_pre + i, argv + i, l);

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

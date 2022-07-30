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

int
asm_runner(const char** paths, int num_files, log_t* l)
{
	asm_pre_t* asm_pre_arr; int i;

	asm_pre_arr = alloca(sizeof(asm_pre_t) * num_files);

	/*
	 * Run pre-assembler.
	 */
	for (i = 0; i < num_files; ++i) {
		const char* p = paths[i];
		asm_pre_t*  a = &(asm_pre_arr[i]);

		log_set_context(l, p);

		if (asm_pre_init(a, p, l) == 0) {

			asm_pre_sheldi(a, l);
		}
	}

	//----------------------------------------------------------------------------------------

	/*
	 * Abstain from writes upon fatal errors.
	 */
	if (log_has_fatal(l)) {
		return -1;
	}

	/*
	 * TODO::write pre assembler files...
	 */
	for (i = 0; i < num_files; ++i) {
	}




	//----------------------------------------------------------------------------------------
	/*
	 * Run assembler.
	 */
//	for (i = 0; i < num_files; ++i) {
//		const char* p = paths[i];
//
//		log_set_context(l, p);
//
//		asm_runner_asm(asm_pre + i, l);
//	
//		if (log_has_fatal(l)) {
//			return -1;
//		}
//	}

	return 0;
}

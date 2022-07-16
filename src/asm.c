#include "include/assembler.h"
#include "include/list.h"
#include "include/scanner.h"

int
asm_run(int argc, const char** argv, log_t* l)
{
	asm_t a = alloca

	/*
	 * Run pre-assembler on source files.
	 */
	for (i = 0; i < argc; ++i) {
	
	}

	/* if errors, get out.. */

	/*
	 * Run assembler on medium files.
	 */
	for (i = 0; i < argc; ++i) {
	
	}

	return 0;

	if (!asm_expend_macros(
	list_t l;
	scanner_t t;
	// load file to list
		// expend macros
		// delete macros
		// convert tags to non-number tags...
		// convert tags to uniqe incrementing tags idx.
		// run pre-assembler checks, tests.
		// use a list to save errors.
		// if list empty
		// write to pre-assembler output.
		// if list not empty
		// 

		// PreAssembler:
		//  - parse args
		//  - do macro expension
		//  - parse statements by \n
			// blank   white spaces line
			// comment ; ...
			// direction
			//    optional label
			//	  XYZ: .data 1,2,3,4,5,-1   ,3	,10
			//		(save XYX=DataCounter, increase DataCounter)
			//	  mov XYZ,r1
			// instruction 

	return 0;
}

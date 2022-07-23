#include "asm.h"
#include "log.h"

static void
asm_parse_lines(asm_t* a, log_t* l)
{
	// run line by line.
	// try convert each const char* to a line_t
	// if lines is faulty, mark it faulty.
	// for each line, hold the following data:
	//  - has label bit
	//  - has data/string/struct/entry/extern bits
	//  - num of parts
	//  - array of parts
	//
}

static void
asm_store_labels(asm_t* a, log_t* l)
{
}

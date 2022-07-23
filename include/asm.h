#ifndef __ASM__
#define __ASM__

#include "log.h"

typedef struct {
	int a;
} asm_t;

void asm_parse_lines(asm_t* a, log_t* l);

void asm_store_labels(asm_t* a, log_t* l);

#endif /*__ASM__*/

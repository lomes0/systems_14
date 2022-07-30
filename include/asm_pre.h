#ifndef __ASM_PRE__
#define __ASM_PRE__

#include "lines.h"
#include "macros.h"
#include "log.h"

typedef struct {
	lines_t* lines;
	lines_t* lines_out;
	macros_t* macros;
} asm_pre_t;

void asm_pre_write_file(asm_pre_t* asm_pre, log_t* l);

void asm_pre_sheldi(asm_pre_t* a, log_t* l);

int asm_pre_init(asm_pre_t* asm_pre, const char* p, log_t* l);

#endif /* __ASM_PRE__ */

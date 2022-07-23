#ifndef __ASM_PRE__
#define __ASM_PRE__

#include "log.h"

typedef struct {
	int a;
} asm_pre_t;


void asm_pre_init(asm_pre_t* asm_pre, const char* p, log_t* l);

void asm_pre_load_source(asm_pre_t* asm_pre, const char* p, log_t* l);

void asm_pre_save_macros(asm_pre_t* asm_pre, log_t* l);

void asm_pre_expend_macros(asm_pre_t* asm_pre, log_t* l);

void asm_pre_write_file(asm_pre_t* asm_pre, log_t* l);

#endif /* __ASM_PRE__ */

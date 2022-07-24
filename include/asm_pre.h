#ifndef __ASM_PRE__
#define __ASM_PRE__

#include "log.h"
#include "lines.h"

typedef struct {
	node_t* start;
	node_t* end;
} sub_list_t;

typedef struct {
	lines_t lines;
	//macros_t macros;
	//macros btree
} asm_pre_t;


//void asm_pre_store_macros(asm_pre_t* asm_pre, log_t* l);

//void asm_pre_expend_macros(asm_pre_t* asm_pre, log_t* l);

void asm_pre_write_file(asm_pre_t* asm_pre, log_t* l);

void asm_pre_sheldi(asm_pre_t* a, log_t* l);

int asm_pre_init(asm_pre_t* asm_pre, const char* p, log_t* l);

#endif /* __ASM_PRE__ */

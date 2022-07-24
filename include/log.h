#ifndef __LOG__
#define __LOG__

#include "common.h"

typedef struct {
	int a;
} log_t;

void log_warn(ret_t r, ...);

void log_err(ret_t r, ...);

void log_fatal(ret_t r, ...);

int log_has_fatal(log_t* l);

void log_flush(log_t* l);

void log_set_context(log_t* l, const char* p);

void log_init(log_t* l);

#endif /*__LOG__*/

#ifndef __LOG__
#define __LOG__

#include "common.h"
#include "list.h"

typedef struct {
	const char* ctx;
	list_t warns;
	list_t errs;
} log_t;

void log_err(log_t* l, const char* fmt, ...);

int log_has_errs(log_t* l);

void log_flush(log_t* l);

void log_set_context(log_t* l, const char* p);

void log_init(log_t* l);

#endif /*__LOG__*/

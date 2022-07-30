#ifndef __LOG__
#define __LOG__

#include "common.h"

typedef enum {
	STATE_FATAL = 0x1,
	STATE_ERR   = 0x2,
	STATE_WARN  = 0x4,
} state_t;

typedef struct {
	state_t flags;
	const char* ctx;
	int bytes_free;
	int bytes_used;
	char* buff;
} log_t;

void log_warn(log_t* l, const char* fmt, ...);

void log_err(log_t* l, const char* fmt, ...);

void log_fatal(log_t* l, const char* fmt, ...);

int log_has_fatal(log_t* l);

void log_flush(log_t* l);

void log_set_context(log_t* l, const char* p);

void log_init(log_t* l);

#endif /*__LOG__*/

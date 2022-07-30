#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define LOG_BLOCK_SIZE	(0x40)

#define log_sprintf(l, fmt, val)                     \
 do {                                                \
   char* prev = l->buff + l->bytes_used;             \
   char* curr = prev;                                \
   curr += snprintf(curr, LOG_BLOCK_SIZE, fmt, val); \
   l->bytes_used += ((curr - prev) / sizeof(char));  \
   l->bytes_free -= ((curr - prev) / sizeof(char));  \
 } while (0)

static void
log_realloc(log_t* l)
{
}

static int
log_low_mem(log_t* l)
{
	return l->bytes_free < LOG_BLOCK_SIZE;
}

static void
log_append(log_t* l, state_t s, const char* fmt, va_list args)
{
	if (log_low_mem(l)) {
		log_realloc(l);	
	}

	switch (s)
	{
		case STATE_ERR:
			log_sprintf(l, "%s", "err: ");
			break;
		case STATE_WARN:
			log_sprintf(l, "%s", "warn: ");
			break;
		case STATE_FATAL:
			log_sprintf(l, "%s", "warn: ");
			break;
	}

	while (*fmt) {

		if (*fmt == '%') {
			if (*fmt == 'c') {
				//char val = (char)va_arg(args, char);
			}

			if (*fmt == 'd') {
				//char val = (int)va_arg(args, int);
			}
		}
	}

}

void
log_err(log_t* l, const char* fmt, ...)
{
    va_list args;
 
    va_start(args, fmt);
 
	log_append(l, STATE_ERR, fmt, args);

	va_end(args);
}

void
log_set_context(log_t* l, const char* p)
{
	l->ctx = p;
}

int
log_has_fatal(log_t* l)
{
	return (l->flags & STATE_FATAL) != 0;
}

void
log_flush(log_t* l)
{
}

void
log_init(log_t* l)
{
	l->flags = 0;
	l->ctx = "";
	l->bytes_free = 2 * LOG_BLOCK_SIZE;
	l->bytes_used = 0;
	l->buff = calloc(2, l->bytes_free);
}

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "log.h"

#define ENTRY_MAX_SIZE (0x80)

static str_t
log_format(const char* fmt, va_list args)
{
	char buff[ENTRY_MAX_SIZE];
	const char* f = fmt;
	char* p = buff;
	str_t msg;

	memcpy(buff, fmt, strlen(fmt) + 1);

	while (*f) {

		if (*f == '%') {
			f++;
			if (*f == 's') {
				char* val = (char*)va_arg(args, char*);
				p += sprintf(p, p, val);
			}
			if (*f == 'd') {
				int val = (int)va_arg(args, int);
				p += sprintf(p, p, val);
			}
		}

		f++;
	}

	str_init_val(&msg, buff);

	return msg;
}

void
log_err(log_t* l, const char* fmt, ...)
{
    va_list args;
    str_t msg;
 
    va_start(args, fmt);
 
	msg = log_format(fmt, args);

	list_append_val(&l->errs, msg.c_str);

	va_end(args);
}

void
log_set_context(log_t* l, const char* p)
{
	l->ctx = p;
}

int
log_has_errs(log_t* l)
{
	return l->errs.len > 0;
}

void
log_flush(log_t* l)
{
	// print warns
	// print errs
}

void
log_init(log_t* l)
{
	l->ctx = "default";
	list_init(&l->warns);
	list_init(&l->errs);
}

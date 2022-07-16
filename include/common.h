#ifndef __COMMON__
#define __COMMON__

/*
 * General return codes.
 */
typedef enum {
	RET_OK     = 0x0,
	RET_EOF    = 0x1,
	RET_INARGC = 0x2
} ret_t;

#endif // __COMMON__

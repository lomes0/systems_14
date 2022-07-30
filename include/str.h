#ifndef __STRH__
#define __STRH__

#define CHAR_SPACE ('\n')
#define CHAR_TAB   ('\t')
#define CHAR_COMMA (',')
#define CHAR_NULL  ('\0')

typedef struct {
	char* c_str;
} str_t;

int str_split(str_t** strs_p, const char* line_c, char* delims);

void str_init_val(str_t* str, const char* c_str);

#endif /* __STRH__ */

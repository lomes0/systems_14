#ifndef __STRINGS__
#define __STRINGS__

#define CHAR_SPACE ('\n')
#define CHAR_TAB   ('\t')
#define CHAR_COMMA (',')
#define CHAR_NULL  ('\0')

int strings_break_by(char** segments, int max_segs, const char* line_c, char* delims);

#endif /* __STRINGS__ */

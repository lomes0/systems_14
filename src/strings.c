#include <string.h>
#include <alloca.h>
#include <stdlib.h>

int
strings_break_by_whites(char** segments, int max_segs, const char* line_c, char* delims)
{
	char* buff; char* p_char;
	int num_bytes; int seg_i;

	num_bytes = (strlen(line_c) + 1) * sizeof(char);
	buff      = alloca(num_bytes);
	memcpy(buff, line_c, num_bytes);

	seg_i = 0;
	p_char = strtok(buff, delims);
	while (p_char != NULL) {
		if (seg_i == max_segs) {
			return max_segs;
		}

		segments[seg_i] = malloc((strlen(p_char) + 1) * sizeof(char));
		memcpy(segments[seg_i], p_char, (strlen(p_char) + 1) * sizeof(char));

		p_char = strtok(NULL, delims);
		seg_i++;
	}

	return seg_i;
}

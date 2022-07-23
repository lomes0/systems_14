#include <stdlib.h>

#include "include/log.h"
#include "include/asm_sh.h"

//	Registers
//		General: r0,...,r7
//			each r_i is a 10 bits.|
//		PSW: program status word (controls cpu state)
//		PC:  points to the memory of the current word beening executed.
//	Memory:
//		0-255 words
//		each word is 10 bits.
//	Numbers:
//		Only positives and negatives.
//		Arithmetic with 2-complements.
//		Suport for ASCII chars.
//
//	Instructions:
//		First Word:
//			| 9   6 | 5    4 | 3    2 | 1   0 |
//			 ---------------------------------
//			|   op  |   src  |   dst  | A,R,E |
//
//			!,@,#,$,%,^,&,*,<,>,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v
//			0,1,2,...                                                    ,31
// 
//		Opcodes:
//			0 mov
//			1 cmp
//			2
//			3
//			4
//			5
//			6
//			7
//			8
//			9
//			10
//			11
//			12
//			13
//			14
//			15
//
//		A,R,E:
//			00 instruction is absolute
//			01 instruction is external
//			10 instruction is relocatable

static int
valid_input_file(const char* arg, log_t* l)
{
	//log_err(R_INFILEP, "%c", "no read permissions");
	return 0;
}

static int
valid_args(int argc, const char** argv, log_t* l)
{
	int i, j;

	/*
	 * Assert positive num of input files.
	 */
	if (argc < 1) {
		/* map ret_code to format */
		log_err(RET_INARGC, argc);
		return -1;
	}

	/*
	 * Assert file type, permissions, existance...
	 */
	for (i = 0; i < argc; ++i) {
		if (!valid_input_file(argv[i], e)) {
			return -1;
		}
	}

	/*
	 * Assert uniqe paths...
	 */
	for (i = 0; i < argc; ++i) {
		for (j = i + 1; j < argc; ++j) {
		}
	}

	return 0;
}
//	if (!valid_args(argc - 1, argv + 1, &l)) {
//		log_flush(&l);
//		return EXIT_FAILURE;
//	}


int
main(int argc, const char** argv)
{
	log_t l;
	log_init(&l);
	int ret;

	asm_sh(argc - 1, argv + 1, &l);

	ret = log_has_fatal(&l) ? EXIT_FAILURE : EXIT_SUCCESS;

	log_flush(&l);

	return ret;
}

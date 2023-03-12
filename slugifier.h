#ifndef _SLUGIFIER_
#define _SLUGIFIER_ 1

#include <stddef.h>

int remove_accents(const char* text, size_t text_length,
		   char** out, size_t* out_length);

int to_dash(unsigned char *in, size_t in_length, unsigned char *out,
	    size_t *out_length);

int slugifier(const char* text, size_t length, unsigned char* output, size_t outputlen);

#endif

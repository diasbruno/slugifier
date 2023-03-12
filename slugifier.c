#include <slugifier.h>
#include <pcre.h>
#include <stdio.h>
#include <string.h>
#include <unac.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#define REMOVE_ACCENTS_MESSAGE "failed to remove accents with unac."
#define OUTPUT_LENGTH_DONT_MATCH_ERROR "output and text must have the same length (%zu, %zu).\n"

int remove_accents(const char* text, size_t text_length,
		   char** out, size_t* out_length) {
  int err = unac_string("UTF-8", text, text_length, out, out_length);

  if (err != 0) {
    fprintf(stderr, REMOVE_ACCENTS_MESSAGE);
    return 1;
  }

  return 0;
}

int to_dash(unsigned char* in, size_t in_length,
	    unsigned char* out, size_t* out_length) {
  int errcode = 0;
  size_t erroffset = 0;

  pcre2_code* re = pcre2_compile((unsigned char*)"[^\\w\\d]",
				 PCRE2_ZERO_TERMINATED,
				 PCRE2_MULTILINE,
				 &errcode, &erroffset,
				 NULL);

  pcre2_substitute(re,
		   in, in_length, 0,
		   PCRE2_SUBSTITUTE_GLOBAL | PCRE2_SUBSTITUTE_EXTENDED,
		   NULL, NULL,
		   (uint8_t*)"-", 1, out, out_length);

  if (errcode != 100) {
    unsigned char emsg[1024] = {0};
    pcre2_get_error_message(errcode, emsg, 1024);
    printf("pcre error: %s\n", emsg);
  }

  free(re);

  return 0;
}

int slugifier(const char* text, size_t length, unsigned char* output, size_t outputlen) {
  char* out = NULL;
  size_t out_length = 0;

  int err = 0;

  err = remove_accents(text, length,
		       &out, &out_length);

  if (err > 0) {
    free(out);
    return err;
  }

  err = to_dash((unsigned char*)out, out_length, output, &outputlen);

  free(out);

  return err;
}

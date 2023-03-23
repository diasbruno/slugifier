#include <slugifier.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>

#define UNUSED(x) ((void)(x))

void usage() {
  printf("usage: slugifr [options] [string]\n");
  printf("               -l remove leading dash.\n");
  printf("               -t remove trailing dash.\n");
  printf("               -h help.\n");
  exit(1);
}

int should_consume(int flag, char the_char) {
  return flag > 0 && !isalnum(the_char) && the_char != '-';
}

int main(int argc, char* argv[]) {
  UNUSED(argc);

  static struct opt_t {
    int remove_leading;
    int remove_trailing;
  } options = {
    0,
    0
  };

  int arg = -1;

  const char* text = argv[argc - 1];
  size_t text_length = text ? strlen(text) : 0;

  if (argc < 2 || text_length == 0) {
    usage(), exit(1);
  }

  while ((arg = getopt(argc - 1, argv, "hlt")) > 0) {
    switch ((char)arg) {
    case 'h': { usage(), exit(1); } break;
    case 'l': { options.remove_leading = 1; } break;
    case 't': { options.remove_trailing = 1; } break;
    default: {}
    }
  }

  size_t stextlen = 1024;
  unsigned char* stext = malloc(stextlen);

  int err = slugifier(text, text_length, stext, stextlen);
  if (err) {
    exit(1);
  }

  size_t rtext_lenght = 1024;
  unsigned char* rtext = malloc(rtext_lenght);

  int should_consume_leading = should_consume(options.remove_leading, text[0]);
  int should_consume_trailing = should_consume(options.remove_trailing, text[text_length - 1]);

  size_t thetext_length = strlen((const char*)stext) -
    (should_consume_leading + should_consume_trailing);

  for (
       int p = 0, cp = should_consume_leading;
       p <= thetext_length;
       p++, cp++
       ) {
    rtext[p] = stext[cp];
  }
  rtext[thetext_length] = 0;

  printf("%s", rtext);

  free(stext);
  free(rtext);
  return err;
}

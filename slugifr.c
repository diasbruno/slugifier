#include <slugifier.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define UNUSED(x) ((void)(x))

void usage() {
  printf("usage: slugifr [string]\n");
  printf("               -h help.\n");
  exit(1);
}

int main(int argc, char* argv[]) {
  UNUSED(argc);

  int arg = -1;

  const char* text = argv[1];
  size_t text_length = text ? strlen(text) : 0;

  if (argc < 2 ||
      text_length == 0 ||
      (char)(arg = getopt(argc, argv, "h")) == 'h') {
    usage();
    exit(1);
  }


  size_t stextlen = 1024;
  unsigned char* stext = malloc(stextlen);

  int err = slugifier(text, text_length, stext, stextlen);
  if (err) {
    exit(1);
  }

  printf("%s", stext);

  free(stext);
  return err;
}

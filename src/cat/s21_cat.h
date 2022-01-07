#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

static struct option const long_options[] = {
  {"number-nonblank", 0, NULL, 'b'},
  {"number", 0, NULL, 'n'},
  {"squeeze-blank", 0, NULL, 's'},
  {"show-nonprinting", 0, NULL, 'v'},
  {"show-ends", 0, NULL, 'E'},
  {"show-tabs", 0, NULL, 'T'},
  {"show-all", 0, NULL, 'A'},
  {NULL, 0, NULL, 0}
};

#endif  // SRC_CAT_S21_CAT_H_

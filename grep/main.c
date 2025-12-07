#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grep.h"

int main(int argc, char *argv[]) {
  int flag = 0;
  if (argc < 2) {
    printf("Usage: %s <pattern> <filename>\n", argv[0]);
    flag = 1;
  } else {
    flags argument = parser(argc, argv);
    if (argument.error == 1) {
      flag = 1;
    }

    else {
      output(&argument, argc, argv);
    }
    if (argument.reg_pattern != 0) {
      free(argument.reg_pattern);
    }
  }
  return flag;
}


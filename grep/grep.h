#ifndef GREP_H
#define GREP_H

#include <regex.h>

#define MAX_LINE_SIZE 1024

typedef struct flags {
  int error;
  int len;
  int memory;
  char *reg_pattern;
  int e, i, v, c, l, n, h, s, f, o, q;
} flags;

void add_pattern(flags *argument, char *pattern);

void reader_regs(flags *argument, char *file_name);

flags parser(int args, char **argv);

void flag_o(regex_t* re, char* line);

void outline(char *line, int n);

FILE *reader(char *file_name);

void comparator(flags *argument, char *file_name, regex_t *reg, int print_file_prefix);

void output(flags *argument, int argc, char **argv);

#endif
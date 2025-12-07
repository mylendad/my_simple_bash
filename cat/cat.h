#ifndef CAT_H
#define CAT_H

#define MAX_LINE_SIZE 1024

typedef struct flags
{
    int error;
    int b, n, e, E, s, t, T, v;
}flags;

flags parser(int argc, char **argv);

void outline(flags *argument, char *line, int n);

void print(char *argv[], flags *flag);

void output (flags *argument, int file_count, char *argv[]);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cat.h"

flags parser(int argc, char **argv) {
    flags argument = {0};
    struct option long_option[] = {
        {"number", no_argument, NULL, 'n'},
        {"number-nonblank", no_argument, NULL, 'b'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {NULL, 0, NULL, 0}
    };
    
    int arguments;
  
    while ((arguments = getopt_long(argc, argv, "bnEesTtv", long_option, 0)) != -1) {
        switch (arguments) {
            case 'b':
                argument.b = 1;
                break;
            case 'n':
                argument.n = 1;
                break;
            case 'E':
                argument.E = 1;
                break;
            case 'e':
                argument.E = 1;
                argument.v = 1;
                break;
            case 's':
                argument.s = 1;
                break;
            case 'T':
                argument.T = 1;
                break;
            case 't':
                argument.T = 1;
                argument.v = 1;
                break;
            case 'v':
                argument.v = 1;
                break;
            default:
                perror("Error");
                argument.error = 1;
                break;
        }
    }
    
    return argument;
}

void outline(flags *argument, char *line, int n) {
    for (int i = 0; i < n; i++) {
        char current_char = line[i];
        
        if (argument->b && argument->n) {
            argument->n = 0;
        }
        
        if (argument->E == 1 && current_char == '\n') {
            putchar ('$');
        }
        
        if (argument->T == 1 && current_char == '\t') {
            putchar ('^');
            current_char = 'I';
        }

        if (argument->v == 1) {
            if (((unsigned char)current_char < 32 && current_char != '\t' && current_char != '\n') || (unsigned char)current_char == 127) {
                putchar('^');
                if ((unsigned char)current_char == 127) {
                    current_char = '?';
                } else {
                    current_char += 64;
                }
            }
        }
        putchar(current_char);
    }
}

void output (flags *argument, int file_count, char **argv) {
    int line_counter = 1; 
    int at_beginning_of_line = 1;
    
    for (int i = 0; i < file_count; i++) {
        FILE *f = fopen(argv[i], "r"); 
        if (f == NULL) {
            perror("Error");
            return; 
        }
        char line[MAX_LINE_SIZE];
        int previous_line_blank = 0;

        while (fgets(line, MAX_LINE_SIZE, f) != NULL) {
            int current_line_blank = (strcmp(line, "\n") == 0);

            if (argument->s == 1 && previous_line_blank && current_line_blank) {
                continue;
            }

            if (at_beginning_of_line) {
                if (argument->b == 1) {
                    if (!current_line_blank) {
                        printf("%6d\t", line_counter++);
                    }
                } else if (argument->n == 1) {
                     printf("%6d\t", line_counter++);
                }
            }

            outline(argument, line, strlen(line));
            
            if (line[strlen(line) - 1] == '\n') {
                at_beginning_of_line = 1;
            } else {
                at_beginning_of_line = 0;
            }
            
            previous_line_blank = current_line_blank;
        }
        fclose(f); 
    } 
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>
#include <errno.h>
#include "grep.h"


#define MAX_LINE_SIZE 1024

flags parser(int argc, char **argv) {
    flags argument = {0}; 
    errno = 22;
    int arguments;
    while ((arguments = getopt(argc, argv, "e:ivclnhsf:oq")) != -1) { 
        switch (arguments)
        {
            case 'e':
                argument.e = 1;
                add_pattern(&argument, optarg); 
                break;
            case 'i':
                argument.i = REG_ICASE;
                break;
            case 'v':
                argument.v = 1;
                break;
            case 'c':
                argument.c = 1;
                break;
            case 'l':
                argument.l = 1;
                break;
            case 'n':
                argument.n = 1;
                break;
            case 'h':
                argument.h = 1;
                break;
            case 's':
                argument.s = 1;
                break;   
            case 'f':
                argument.f = 1;
                reader_regs(&argument, optarg);
                break; 
            case 'o':
                argument.o = 1;
                break;
            case 'q': 
                argument.q = 1;
                break;
            default:
                perror("ErrorParser");
                argument.error = 1;
                break; 
            }
        }
            if (argument.len == 0 && optind < argc) { 
                    add_pattern(&argument, argv[optind]); 
                optind++;
            }
        if (argument.reg_pattern == 0) {
            perror("No pattern.\n");
            argument.error = 1;
        }
    return argument;
}

void add_pattern(flags *argument, char *pattern) {
    int len_pattern = strlen(pattern);
  
    if (argument->len == 0) {
        argument->reg_pattern = malloc((len_pattern + 4 ) * sizeof(char));
        }
    if (len_pattern < len_pattern + argument->len) {
        argument->reg_pattern = realloc(argument->reg_pattern, (len_pattern + argument->len + 4) * sizeof(char));
        }
    if (argument->len > 0) {
        strcat(argument->reg_pattern, "|");
        argument->len++;
    }
    argument->len = argument->len + (sprintf(argument->reg_pattern + argument->len, "(%s)", pattern)); 
    

}

void reader_regs(flags *argument, char *file_name) {
   
    FILE *f = reader(file_name);

     if (f == 0) {
        if (argument->s == 0) { 
            perror(file_name);
        }
        return;
    }
    char line[MAX_LINE_SIZE];
    int line_counter = 0;
   
        while (fgets(line, sizeof(line), f) != NULL) {
            
            if (line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = '\0';
            }
            add_pattern(argument, line);
            line_counter++;
            
    }
    fclose(f);
}

void flag_o(regex_t* re, char* line) {
    regmatch_t match;
    int shift = 0;
    int result;
    while ((result = regexec(re, line + shift, 1, &match, 0)) == 0) {
         for (int i = match.rm_so; i < match.rm_eo; i++) {
            putchar(line[i]); 
        }
        putchar('\n');
        shift += match.rm_eo;
    }
}

void outline(char *line, int n) {
    for (int count_filename = 0; count_filename < n; count_filename++) {
        putchar(line[count_filename]); 
    }
    if (line[n - 1] != '\n') {
        putchar('\n');
    }
}
FILE *reader(char *file_name) {
       FILE* f = fopen(file_name, "r");
    return f;
}

void comparator(flags *argument, char *file_name, regex_t *reg, int print_file_prefix) { 
    FILE *f = reader(file_name);
    if (f == 0) {
        if (argument->s == 0) { 
            perror(file_name);
        }
        return;
    }
    char line[MAX_LINE_SIZE];
    int count_reg = 0; 
    int line_counter = 1;
        while (fgets(line, sizeof(line), f) != NULL) {
            int result = regexec(reg, line, 0, NULL, 0); 
            
            int should_output_match = (result == 0 && argument->v == 0) || (result != 0 && argument->v == 1);

            if (argument->o == 1 && argument->v == 1) {
                should_output_match = 0; 
            }

            if (should_output_match && argument->c == 0 && argument->l == 0){ 
        
                if (print_file_prefix){
                    printf("%s:", file_name);
                }
                if (argument->n == 1) {
                printf("%d:", line_counter);
                }   
                if (result == 0  && argument->o == 1) { 
                 flag_o(reg, line);
                
                }   
                else {
                    outline(line, strlen(line));
                }
                } 
           line_counter++;
        
        if ((argument->c == 1 || argument->l == 1 )&& result == 0) {
                    count_reg++;
                }
        }
        if (count_reg > 0  && argument->l == 1) {
            if (print_file_prefix) { 
                printf("%s\n", file_name);
            } else {
                printf("%s\n", file_name);
            }
        }
        if (argument->c == 1){ 
            if (print_file_prefix) { 
                printf("%s:", file_name);
            }
            printf("%d\n", count_reg);    
        }
            fclose(f);
}

void output (flags *argument, int argc, char **argv) {
    if (argument->q == 1) {
        return;
    }
    
    regex_t reg; 
    if (regcomp(&reg, argument->reg_pattern, REG_EXTENDED | argument->i) != 0) { 
        if (argument->s == 0) { 
            perror ("ErrorOutput");
        }
       return;
    }
    
    int file_count = argc - optind;
    int print_file_prefix = (file_count > 1 && argument->h == 0); 

    for (int i = optind; i < argc; i++) {      
        comparator(argument, argv[i], &reg, print_file_prefix); 
    }
    regfree(&reg); 
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "cat.h"

int main(int argc, char *argv[]) {
    flags argument = parser(argc, argv);
    if (argument.error) {
        return 1;
    }

    if (argument.b) {
        argument.n = 0;
    }

    output(&argument, argc - optind, &argv[optind]);
    return 0;
}
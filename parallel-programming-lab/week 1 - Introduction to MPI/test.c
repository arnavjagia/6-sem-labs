#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int toggleCase(int c) {
    return c ^ ('A' ^ 'a');
}

int main(int argc, char *argv[]) {
    printf("%d\t%s\n", argc, *argv);
    printf("%d\n", ' ' ^ ('a' ^ 'A'));
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"


int main(int argc, char  *argv[])
{
    char * file_path = argv[1];
    // char * file_path = "test";
    FILE* f = fopen(file_path, "rb");
    uint64_t file_size = get_file_size(file_path);
    // printf("%d\n", get_file_size(file_path));
    printf("\nHEX OUTPUT\n");
    dump_bin(f, 1, 10, true, true, file_size, D_HEXADECIMAL);

    return 0;
}

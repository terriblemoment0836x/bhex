#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


int main(int argc, char  *argv[])
{
    char * file_path = argv[1];
    FILE* f = fopen(file_path, "rb");
    uint64_t file_size = get_file_size(file_path);
    // printf("%d\n", get_file_size(file_path));
    print_oct(f, 1, 8, true, file_size);

    return 0;
}

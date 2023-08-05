#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "dump.h"


int main(int argc, char  *argv[])
{
    struct settings* params = init_settings();

    // if ( argc <= 1 ) {
    //     show_help();
    //     return 0;
    // }

    parse_arguments(argc, argv, params);

    print_settings(params);
    
    // // char * file_path = "test";
    // char * file_path = argv[1];
    // FILE* f = fopen(file_path, "rb");
    // uint64_t file_size = get_file_size(file_path);
    // // printf("%d\n", get_file_size(file_path));
    // printf("HEX OUTPUT:\n");
    // dump_bin(f, 2, 10, true, true, true, file_size, D_HEXADECIMAL);

    free_settings(params);

    return 0;
}

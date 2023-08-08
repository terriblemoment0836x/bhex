#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "dump.h"


int main(int argc, char  *argv[])
{
    struct settings* params = init_settings();

    if ( parse_arguments(argc, argv, params) == false ) {
        exit(1);
    }

    // print_settings(params);
    
    char * file_path = params->file_path;
    FILE* f = fopen(file_path, "rb");
    uint64_t file_size = get_file_size(file_path);
    dump_bin(f, params->column_size, params->column_count,
             params->enable_address, params->enable_ascii, params->enable_color,
             file_size, params->number_type);

    fclose(f);
    free_settings(params);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "dump.h"


int main(int argc, char  *argv[])
{
    struct settings* params = init_settings();

    if ( parse_arguments(argc, argv, params) == false ) {
        return 1;
    }

    FILE* fd = fopen(params->file_path, "rb");

    if ( fd == NULL ) {
        perror("Error opening the file: ");
        perror(params->file_path);
        perror(".\n");

        free_settings(params);
        return 1;
    }

    bool dump_status = dump_bin(fd, params->column_size, params->column_count,
             params->enable_address, params->enable_ascii, params->enable_color,
             params->number_type);

    if ( dump_status == false ) {
        perror("An error occured while dumping the file.\n");
    }

    fclose(fd);
    free_settings(params);

    return 0;
}

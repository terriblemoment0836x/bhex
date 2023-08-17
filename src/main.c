#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "dump.h"
#include "search.h"


int main(int argc, char  *argv[])
{

    struct settings* params = init_settings();

    if ( parse_arguments(argc, argv, params) == false ) {
        return 1;
    }

    // print_settings(params);
    // return 0;

    FILE* fd = fopen(params->file_path, "rb");

    if ( fd == NULL ) {
        perror("Error opening the file: ");
        perror(params->file_path);
        perror(".\n");

        free_settings(params);
        return 1;
    }


    uint64_t file_size = get_file_size(params->file_path);

    if ( enable_terminal_color() == false ) params->enable_color = false;

    if ( SetConsoleCtrlHandler(handle_ctrl_c, TRUE) == 0 ) {
        GetLastError();
    }

    if ( params->search_file == true ) {
        search_file(fd, params);
    } else {
        bool dump_status = dump_bin(fd, params->column_size, params->column_count,
                                    params->enable_address, params->enable_ascii, params->enable_color,
                                    params->number_type, digit_count(16, file_size), 0, 0);

        if (dump_status == false)
        {
            perror("An error occured while dumping the file.\n");
        }
    }


    fclose(fd);
    free_settings(params);

    return 0;
}

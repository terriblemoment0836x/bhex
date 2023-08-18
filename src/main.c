#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#else
#include <signal.h>
#endif

#include "config.h"
#include "utils.h"
#include "dump.h"
#include "search.h"

#ifndef HAVE_WINDOWS_H
static void handle_sigterm(int signo) {
        printf("\x1b[0;m");
}
#endif


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

#ifdef HAVE_WINDOWS_H
    if ( enable_terminal_color() == false ) params->enable_color = false;

    if ( SetConsoleCtrlHandler(handle_ctrl_c, TRUE) == 0 ) {
        GetLastError();
    }
#else
    if ( signal(SIGTERM, handle_sigterm) == SIG_ERR ) {
        perror("Can't set handler for SIGTERM.\n");
    }
#endif

    if ( params->search_file == true ) {
       params->search_pattern_len = parse_hex_string(params->search_pattern);
        // for (int i = 0; i < length; i++) {
        //     printf("0x%x ", params->search_pattern[i]);
        // }
        // printf("\n");
        // return 0;
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

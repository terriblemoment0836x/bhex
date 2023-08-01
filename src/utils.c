#include "utils.h"

uint64_t get_file_size(char * file_path) {
    HANDLE hfile = CreateFile(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if ( hfile == INVALID_HANDLE_VALUE) {
        perror("Error calculating the size of the file.");
        exit(1);
    }
    
    LARGE_INTEGER size;
    GetFileSizeEx(hfile, &size);

    CloseHandle(hfile);

    return size.QuadPart;
}

uint8_t dump_bin(FILE* fd, uint32_t column_size, uint32_t column_count,
    bool show_address, bool show_ascii,
    uint64_t file_size, enum num_types number_type) {
    unsigned char buff[FREAD_BUFF_SIZE];
    uint32_t byte_written = 0;
    uint32_t separator_written = 0;
    uint32_t line_begin_index = 0;
    int i;
    char printf_template[21];

    switch(number_type) {
        case D_HEXADECIMAL:
            strcpy(printf_template, "%02x");
            break;
        case D_OCTAL:
            strcpy(printf_template, "%03o");
            break;
        case D_BINARY:
            strcpy(printf_template, "%c%c%c%c%c%c%c%c");
            break;
        default:
            return 2;
    }

    if (show_address == true) printf("0x%014x:\t", 0x0);
    while ( byte_written < file_size)
    {
        fread(buff, sizeof(unsigned char), FREAD_BUFF_SIZE, fd);
        int max_print = min(FREAD_BUFF_SIZE, file_size - byte_written);
        for ( i = 0; i < max_print; i++) {
            if ( number_type == D_BINARY)
                printf(printf_template, PRINTF_BIN_ARG(buff[i]));
            else
                printf(printf_template, buff[i]);

            byte_written++;
            
            if ( byte_written % column_size == 0){
                printf(" ");
                separator_written++;
            } 
            if ( separator_written != 0 && separator_written % column_count == 0 && show_ascii == true) {
                printf(" [");
                for ( int j = line_begin_index; j <= i; j++) {
                    if ( buff[j] >= 36 && buff[j] <= 126)
                        printf("%c", buff[j]);
                    else printf(".");
                }
                printf("]");
                line_begin_index = i+1;
                printf("\n"); 
                if (show_address == true)
                    printf("%#016x:\t", byte_written);
                separator_written = 0;
                }
        }
        if ( show_address == true && (separator_written == 0 || separator_written % column_count != 0))
        {
                printf(" [");
                for (int j = line_begin_index; j < i; j++)
                {
                    if ( buff[j] >= 36 && buff[j] <= 126)
                        printf("%c", buff[j]);
                    else printf(".");
                }
                printf("]\n");
        }
    }

    return 0;
}
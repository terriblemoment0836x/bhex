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

uint8_t print_hex(FILE* fd, uint32_t column_size, uint32_t column_count, bool show_address, uint64_t file_size) {
    unsigned char buff[FREAD_BUFF_SIZE];
    uint32_t byte_written = 0;

    printf("%#016x:\t", byte_written);
    while ( byte_written < file_size)
    {
        fread(buff, sizeof(unsigned char), FREAD_BUFF_SIZE, fd);
        int max_print = min(FREAD_BUFF_SIZE, file_size - byte_written);
        for ( int i = 0; i < max_print; i++) {
            printf("%02x", buff[i]);
            byte_written++;
            
            if ( byte_written % column_size == 0)  printf(" ");
            if ( byte_written % column_count*column_size == 0) {
                printf("\n"); 
                printf("%#016x:\t", byte_written);
                }
        }

    }

    return 0;
}
uint8_t print_oct(FILE* fd, uint32_t column_size, uint32_t column_count, bool show_address, uint64_t file_size) {
    unsigned char buff[FREAD_BUFF_SIZE];
    uint32_t byte_written = 0;

    printf("%#016o:\t", byte_written);
    while ( byte_written < file_size)
    {
        fread(buff, sizeof(unsigned char), FREAD_BUFF_SIZE, fd);
        int max_print = min(FREAD_BUFF_SIZE, file_size - byte_written);
        for ( int i = 0; i < max_print; i++) {
            printf("%03o", buff[i]);
            byte_written++;
            
            if ( byte_written % column_size == 0)  printf(" ");
            if ( byte_written % column_count*column_size == 0) {
                printf("\n"); 
                printf("%#016o:\t", byte_written);
                }
        }

    }

    return 0;
}
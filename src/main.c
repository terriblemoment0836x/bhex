#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <fileapi.h>

#define FREAD_BUFF_SIZE 512

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

void print_hex(FILE* fd, uint32_t column_size, uint32_t column_count, bool show_address, uint64_t file_size) {
    unsigned char buff[FREAD_BUFF_SIZE];
    uint32_t byte_written = 0;
    

    printf("%08x:\t", byte_written);
    while ( byte_written < file_size)
    {
        fread(buff, sizeof(unsigned char), FREAD_BUFF_SIZE, fd);
        int max_print = min(FREAD_BUFF_SIZE, file_size - byte_written);
        for ( int i = 0; i < max_print; i++) {
            printf("%02x", buff[i]);
            byte_written++;
        }

        // for (int i = 0; i < BUFSIZ && byte_read < file_size; i++) {
        //     printf("%02x", buff[i]);
        //     byte_written++;

        //     if (byte_read % column_size == 0)
        //         printf(" ", byte_read);
        //     if (byte_read % ((column_size)*column_count) == 0)
        //     {
        //         printf("\n");
        //         if (!feof(fd) && show_address)
        //             printf("%08x:\t", byte_read);
        //     }
        // }

    }
    
}

int main(int argc, char  *argv[])
{
    char * file_path = argv[1] ;
    FILE* f = fopen(file_path, "rb");
    uint64_t file_size = get_file_size(file_path);
    // printf("%d\n", get_file_size(file_path));
    print_hex(f, 3, 6, false, file_size);

    return 0;
}

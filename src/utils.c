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
uint8_t dump_bin(FILE *fd, uint32_t column_size, uint32_t column_count,
                 bool show_address, bool show_ascii,
                 uint64_t file_size, enum num_types number_type)
{
    assert(fd != NULL);
    assert(column_count != 0 && column_size != 0);

    const uint32_t line_size = column_count*column_size;
    uint64_t buffer_size = file_size + line_size;
    buffer_size -= buffer_size % line_size;
    
    printf("file size = %d, line size = %d so the buffer size is = %d\n", file_size, line_size, buffer_size);
    uint32_t bytes_read;
    uint32_t buffer_index;
    uint32_t line_end;
    uint8_t input_buffer[buffer_size];
    uint8_t t;
    const uint8_t ascii_distance = 8;
    uint32_t file_position = 0;

    do {
        bytes_read = fread(input_buffer, sizeof(char), buffer_size, fd);
        buffer_index = 0;

        while ( buffer_index < bytes_read ) {
            line_end = min(buffer_index + line_size, bytes_read);

            t = printf("0x%#08x:\t", file_position + buffer_index);
            print_line_dump(input_buffer, buffer_index, line_end, column_size, number_type);

            printf("\r");
            printf("%c[%dC", 0x1B, 2*line_size + column_count + ascii_distance + t);

            print_line_ascii(input_buffer, buffer_index, line_end);

            printf("\n");

            buffer_index += line_size;
        }
        file_position += buffer_index;

    } while ( bytes_read == buffer_size );
    printf("0x%#08x:\t", file_position);

    assert(!ferror(fd));

    return 0;
    
}
uint8_t print_line_dump(uint8_t * buff, uint32_t start, uint32_t end, uint32_t column_size, enum num_types number_type) {
    char printf_template[20];
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
        for (unsigned int i = start; i < end; i++) {
            if ( number_type == D_BINARY)
                printf(printf_template, PRINTF_BIN_ARG(buff[i]));
            else
                printf(printf_template, buff[i]);
            
            if ( (i+1) % column_size == 0) printf(" ");
        }
        return 0;
}

void print_line_ascii(uint8_t * buff, uint32_t start, uint32_t end) {
    char temp = buff[end];
    buff[end] = '\0';
    printf("[");
    while ( start < end ) {
            if (buff[start] >= 36 && buff[start] <= 126)
                printf("%c", buff[start]);
            else printf(".");
            ++start;
    }
    printf("]");
    buff[end] = temp;
}
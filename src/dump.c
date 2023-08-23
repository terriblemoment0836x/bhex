#include "dump.h"

bool dump_bin(FILE *fd, uint32_t column_size, uint32_t column_count,
                 bool show_address, bool show_ascii, bool enable_colors,
                 enum num_types number_type, uint32_t address_digit_count,
                 uint32_t start_address, int line_count)
{
    if (fd == NULL) return false;
    if (column_count == 0 || column_size == 0) return false;
    switch (number_type) {
        case D_HEXADECIMAL:
        case D_BINARY:
        case D_OCTAL:
            break;
        default:
            return false;
    }

    const uint32_t line_size = column_count*column_size;
    uint64_t buffer_size = line_size * 100;
    uint32_t bytes_read;
    uint32_t buffer_index;
    uint32_t line_end;
    uint8_t *input_buffer = (uint8_t *) malloc(sizeof(uint8_t) * buffer_size);
    uint8_t t = 0;
    const uint8_t ascii_distance = 8;
    uint32_t file_position = 0;
    uint8_t till_end = line_count == 0;

    do {
        bytes_read = fread(input_buffer, sizeof(char), buffer_size, fd);
        buffer_index = 0;

        while ( buffer_index < bytes_read  && (line_count-- > 0 || till_end == 1)) {
            line_end = min(buffer_index + line_size, bytes_read);

            if (show_address == true) {
                t = printf("0x%0*x:\t", address_digit_count, file_position + buffer_index + start_address);
            }

            if ( print_line_dump(input_buffer, buffer_index, line_end, column_size, number_type, enable_colors) == false ) 
                return false;

            if (show_ascii == true) {
                printf("\r");
                printf("%c[%dC", 0x1B, number_type * line_size + column_count + ascii_distance + t);
                print_line_ascii(input_buffer, buffer_index, line_end, enable_colors);
            }

            printf("\n");

            buffer_index = line_end;
        }
        file_position += buffer_index;

    } while ( bytes_read == buffer_size );

    if ( ferror(fd) ) return false;

    if (show_address == true) printf("0x%0*x:\n", address_digit_count, file_position + start_address);

    free(input_buffer);

    return true;
    
}
bool print_line_dump(uint8_t * buff, uint32_t start, uint32_t end, uint32_t column_size, enum num_types number_type, bool enable_color) {
    static uint8_t color_code = 1;
    char printf_template[20];

    switch(number_type) {
        case D_HEXADECIMAL:
            // strcpy(printf_template, "%c");
            strcpy(printf_template, "%02x");
            break;
        case D_OCTAL:
            strcpy(printf_template, "%03o");
            break;
        case D_BINARY:
            strcpy(printf_template, "%c%c%c%c%c%c%c%c");
            break;
        default:
            return false;
    }

    for (unsigned int i = start; i < end; i++)
    {
            if (enable_color == true && configure_color(buff[i], color_code, i == end - 1) == true) {
                color_code = (color_code == 228) ? 1 : color_code + 1;
            }

            if (number_type == D_BINARY)
                printf(printf_template, PRINTF_BIN_ARG(buff[i]));
            else
                printf(printf_template, buff[i]);

            if ((i + 1) % column_size == 0)
                printf(" ");
    }

    printf("%c[0m", 0x1b);
    return true;
}

void print_line_ascii(uint8_t * buff, uint32_t start, uint32_t end, bool enable_color) {
    static uint8_t color_code = 1;

    printf("[");

    while ( start < end ) {
            if ( enable_color == true && configure_color(buff[start], color_code, start == end - 1) == true ) {
                color_code = (color_code == 228) ? 1 : color_code + 1;
            }

            if (buff[start] >= 36 && buff[start] <= 126) {
                printf("%c", buff[start]);
            }
            else {
                printf(".");
            }

            ++start;
    }

    printf("%c[0m", 0x1b);
    printf("]");
}


bool configure_color(uint8_t c, uint8_t color_code, uint8_t reset) {
    static bool color_enabled = false;

    if (c >= 36 && c <= 126) { // c in printable
        if (color_enabled != true) {
            color_enabled = true;
            printf("%c[38;5;%dm", 0x1b, color_code);
        }

        if ( reset ) color_enabled = ! reset;

        return false;
    }

    color_enabled = false;
    printf("%c[0m", 0x1b);
    return true;
}

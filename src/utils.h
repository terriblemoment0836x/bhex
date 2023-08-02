
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <fileapi.h>
#include <assert.h>

// Read buffer size used by dump_bin
#define FREAD_BUFF_SIZE 7

#define PRINTF_BIN_ARG(num) \
    ( (num) & 0b10000000 ? '1' : '0'), ( (num) & 0b01000000 ? '1' : '0'), \
    ( (num) & 0b00100000 ? '1' : '0'), ( (num) & 0b00010000 ? '1' : '0'), \
    ( (num) & 0b00001000 ? '1' : '0'), ( (num) & 0b00000100 ? '1' : '0'), \
    ( (num) & 0b00000010 ? '1' : '0'), ( (num) & 0b00000001 ? '1' : '0')

enum num_types {
    D_BINARY = 8, D_HEXADECIMAL = 2, D_OCTAL = 3
};


/// @brief Return the file size in bytes of a file 
/// @param file_path Path of the file
/// @return File size
uint64_t get_file_size(char * file_path);

/// @brief Print to stdout a formated hex dump of a file specified by fd.
/// @param fd: FILE* returned by a fopen call
/// @param column_size Number of bytes in each column
/// @param column_count Number of columns
/// @param show_address Whether to show the address of the bytes in the file or not.
/// @param file_size The size of the file
/// @return 1: if there is an error reading the file, 2: if there is an error writing to stdout otherwise 0
/// @todo return 1 or 2 on errors;
/// @todo make the address relative to the file size
uint8_t dump_bin(FILE* fd, uint32_t column_size, uint32_t column_count,
    bool show_address, bool show_ascii,
    uint64_t file_size, enum num_types number_type);

uint8_t print_line_dump(uint8_t * buff, uint32_t start, uint32_t end, uint32_t column_size, enum num_types number_type);
void print_line_ascii(uint8_t * buff, uint32_t start, uint32_t end);
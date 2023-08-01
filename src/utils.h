
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <fileapi.h>

#define FREAD_BUFF_SIZE 1024

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
uint8_t print_hex(FILE* fd, uint32_t column_size, uint32_t column_count, bool show_address, uint64_t file_size);
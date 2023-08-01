
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <fileapi.h>

#define FREAD_BUFF_SIZE 1024

uint64_t get_file_size(char * file_path);
void print_hex(FILE* fd, uint32_t column_size, uint32_t column_count, bool show_address, uint64_t file_size);
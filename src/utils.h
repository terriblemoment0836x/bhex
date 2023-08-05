#ifndef _H_UTILS_
#define _H_UTILS_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <fileapi.h>
#include <assert.h>


/// @brief Generate character arguments to printf that represets the binary representation of num.
#define PRINTF_BIN_ARG(num) \
    ( (num) & 0b10000000 ? '1' : '0'), ( (num) & 0b01000000 ? '1' : '0'), \
    ( (num) & 0b00100000 ? '1' : '0'), ( (num) & 0b00010000 ? '1' : '0'), \
    ( (num) & 0b00001000 ? '1' : '0'), ( (num) & 0b00000100 ? '1' : '0'), \
    ( (num) & 0b00000010 ? '1' : '0'), ( (num) & 0b00000001 ? '1' : '0')

/// @brief Base of the numbers in the dump, used also to represent the number of digits of each number
enum num_types {
    D_BINARY = 8, D_HEXADECIMAL = 2, D_OCTAL = 3
};

/// @struct settings
/// @brief Settings used by the program
/// @var settings::enable_color 
/// Self explanatory
/// @var settings::enable_address 
/// Wheter to show the address column in the left
/// @var settings::enable_ascii
/// Self explanatory
/// @var settings::column_size
/// Number of numbers in each column
/// @var settings::column_count
/// Number of columns
/// @var settings::number_type
/// Dump type (hex, bin or oct)
struct settings {
    bool enable_color;
    bool enable_address;
    bool enable_ascii;
    uint32_t column_size;
    uint32_t column_count;
    enum num_types number_type;
};
/// @brief Return a pointer to settings structure containing the default settings.
/// @return Pointer to the settings structure.
struct settings* init_settings();

/// @brief Reflect the argument to the settings structure
/// @param argc Number of arguments
/// @param argv Pointer to array of argument strings
/// @param Pointer to the settings structure.
/// @return false if the command line arguments are invalid, else return true
bool parse_arguments(int argc, char **argv, struct settings* params);


/// @brief Return the file size in bytes of a file 
/// @param file_path Path of the file
/// @return File size
uint64_t get_file_size(char * file_path);

/// @brief Print to stdout a dump of a file specified by fd.
/// @param fd: FILE* returned by a fopen call
/// @param column_size Number of bytes in each column
/// @param column_count Number of columns
/// @param show_address Whether to show the address of the bytes in the file or not.
/// @param file_size The size of the file
/// @return 1: if there is an error reading the file, 2: if there is an error writing to stdout otherwise 0
/// @todo return 1 or 2 on errors;
/// @todo make the address relative to the file size
uint8_t dump_bin(FILE* fd, uint32_t column_size, uint32_t column_count,
    bool show_address, bool show_ascii, bool enable_colors,
    uint64_t file_size, enum num_types number_type);

/// @brief Print to stdout buff from start to end as hex, bin or oct specified by number_type
/// @param buff pointer to char buffer
/// @param start Start index
/// @param end End index
/// @param column_size size of each column
/// @param number_type type of dump hex, bin or oct
/// @param enable_color whether to enable color or not
/// @return 0 on success and 1 on error
uint8_t print_line_dump(uint8_t * buff, uint32_t start, uint32_t end, uint32_t column_size, enum num_types number_type, bool enable_color);

/// @brief Print the ascii part of the dump
/// @param buff pointer to the buffer
/// @param start Start index
/// @param end End index
/// @param enable_color whether to enable color or not
void print_line_ascii(uint8_t * buff, uint32_t start, uint32_t end, bool enable_color);

/// @brief Print the approperiate color terminal sequence based on the current character in the buffer.
/// @param c the caracter in the current buffer.
/// @param color_code Number that represents the color https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#text-formatting
/// @param reset Disable coloring (used by the final call of a function to make this function reading for an other use).
/// @return Whether the color need to change or not (its true when c in not a printable character).
bool configure_color(uint8_t c, uint8_t color_code, uint8_t reset);

#endif
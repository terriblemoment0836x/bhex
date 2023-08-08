#ifndef _H_DUMP_
#define _H_DUMP_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "utils.h"


/// @brief Generate character arguments to printf that represets the binary representation of num.
#define PRINTF_BIN_ARG(num) \
    ( (num) & 0b10000000 ? '1' : '0'), ( (num) & 0b01000000 ? '1' : '0'), \
    ( (num) & 0b00100000 ? '1' : '0'), ( (num) & 0b00010000 ? '1' : '0'), \
    ( (num) & 0b00001000 ? '1' : '0'), ( (num) & 0b00000100 ? '1' : '0'), \
    ( (num) & 0b00000010 ? '1' : '0'), ( (num) & 0b00000001 ? '1' : '0')

/// @brief Print to stdout a dump of a file specified by fd.
/// @param fd: FILE* returned by a fopen call
/// @param column_size Number of bytes in each column
/// @param column_count Number of columns
/// @param show_address Whether to show the address of the bytes in the file or not.
/// @param show_ascii Whether to show the ascii decoding of each line
/// @param enable_colors Whether to show matching colors for strings in th dump and the ascii parts.
/// @param number_type A enum num_types representing the base used for the dump.
/// @return false on error and true on success.
bool dump_bin(FILE* fd, uint32_t column_size, uint32_t column_count,
    bool show_address, bool show_ascii, bool enable_colors,
    enum num_types number_type);

/// @brief Print to stdout buff from start to end as hex, bin or oct specified by number_type
/// @param buff pointer to char buffer
/// @param start Start index
/// @param end End index
/// @param column_size size of each column
/// @param number_type type of dump hex, bin or oct
/// @param enable_color whether to enable color or not
/// @return true on success and false on error
bool print_line_dump(uint8_t * buff, uint32_t start, uint32_t end, uint32_t column_size, enum num_types number_type, bool enable_color);

/// @brief Print the ascii part of the dump
/// @param buff pointer to the buffer
/// @param start Start index
/// @param end End index
/// @param enable_color whether to enable color or not
void print_line_ascii(uint8_t * buff, uint32_t start, uint32_t end, bool enable_color);

/// @brief Print the approperiate color terminal sequence based on the current character in the buffer.
/// @param c the caracter in the current buffer.
/// @param color_code Number that represents the color.
/// See <a href="https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#text-formatting">The documentation</a>
/// @param reset Disable coloring (used by the final call of a function to make this function reading for an other use).
/// @return Whether the color need to change or not (its true when c in not a printable character).
bool configure_color(uint8_t c, uint8_t color_code, uint8_t reset);

#endif
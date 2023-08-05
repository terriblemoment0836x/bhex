#ifndef _H_UTILS_
#define _H_UTILS_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <fileapi.h>
#include <assert.h>

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
void free_settings(struct settings* param);

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

#endif
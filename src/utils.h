#ifndef _H_UTILS_
#define _H_UTILS_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
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
    char * file_path;
    bool enable_color;
    bool enable_address;
    bool enable_ascii;
    uint32_t column_size;
    uint32_t column_count;
    enum num_types number_type;
};

/// @brief Return a pointer to settings structure containing the default settings.
/// @return Pointer to the settings structure or NULL on error.
struct settings* init_settings();

/// @brief Print the structure settings
/// @param Pointer to the structure
void print_settings(struct settings* param);

/// @brief Free the dynamically allocated settings structure.
void free_settings(struct settings* param);

/// @brief Reflect the argument to the settings structure
/// @param argc Number of arguments
/// @param argv Pointer to array of argument strings
/// @param params Pointer to the settings structure.
/// @return false if the command line arguments are invalid, else return true
bool parse_arguments(int argc, char **argv, struct settings* params);

/// @brief Show the program usage.
void show_help();

/// @brief Convert a number in str to uint32.
/// @param str Number as string.
/// @param status Pointer to bool used to indicate if the conversion is succesfull (set to true) or not (set to false).
/// @return The converted number.
uint32_t str_to_posint32(char *str, bool *status);

/// @brief Return the file size in bytes of a file 
/// @param file_path Path of the file
/// @return File size
// uint64_t get_file_size(char * file_path);

#endif
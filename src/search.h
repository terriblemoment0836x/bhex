#ifndef _H_SEARCH_
#define _H_SEARCH_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils.h"

/// @brief Search for the first occurence of pattern in buffer using the bad character heuristic and return its starting position.
/// @param buffer Buffer where the function will search for the pattern.
/// @param buffer_size size of buffer
/// @param pattern The pattern to be searched for.
/// @param pattern_size size of pattern
/// @return The starting position of the pattern or -1 if it's not found.
uint32_t buffer_search(uint8_t *buffer, uint32_t buffer_size,
                       uint8_t *pattern, uint32_t pattern_size,
                       uint32_t *preproccessing_array);

uint32_t *buffer_search_preproccess(uint8_t *pattern, uint32_t pattern_size);

/// @brief Show where params->search_pattern exists in a file.
/// @param fd FILE* pointer returned by fopen.
/// @param params settings structure pointer represeting the program options.
/// @return true if the params->search_pattern is found, false otherwise.
bool search_file(FILE* fd, struct settings* params);

#endif
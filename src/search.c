#include "search.h"


uint32_t *buffer_search_preproccess(uint8_t *pattern, uint32_t pattern_size) {
    int i;
    int j;
    uint32_t *preproccessing_array = (uint32_t*) malloc(sizeof(uint32_t) * 256); // 255 is the alphabet length

    assert(preproccessing_array != NULL);

    for (i = 0; i < 256; i++) {
        preproccessing_array[i] = pattern_size;
    }

    for (i = 0; i < (int)pattern_size; i++) {
        for (j = pattern_size - 1; j >= i; j--) {
            if (pattern[i] == pattern[j]) break;
        }
        preproccessing_array[pattern[j]] = pattern_size - 1 - j;
    }

    return preproccessing_array;
}

uint32_t buffer_search(uint8_t *buffer, uint32_t buffer_size, uint8_t *pattern, uint32_t pattern_size, uint32_t *preproccessing_array) {
    int i = pattern_size - 1;
    int j, t;

    while ( i < (int)buffer_size ) {
        j = pattern_size - 1;
        t = i;
        if ( buffer[t] == pattern[j] ) {
            do {
                j--;
                t--;
            }
            while ( j >= 0 && buffer[t] == pattern[j]);
            if ( j == -1 ) return i - ( pattern_size - 1);
        }
        const int matched_caracters = pattern_size - 1 - j;
        const int shift_width = preproccessing_array[buffer[t]];
        i += max(1, (int)(shift_width - matched_caracters));

    }
    return -1;
}

bool search_file(FILE* fd, struct settings* params) {

}
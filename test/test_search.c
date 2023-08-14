#include <string.h>
#include "../src/search.h"
#include <stdint.h>

int test_buffer_search_preproccess() {

                  //                         1
                  //               01234567890
    uint8_t *pattern = (uint8_t *)"hello world";
    uint32_t pattern_len = strlen((char *)pattern);
    uint32_t *pr_array = buffer_search_preproccess(pattern, pattern_len);

    if ( pr_array[pattern[10]] != pattern_len - 1 - 10 ) return 1;
    if ( pr_array[pattern[9]] != pattern_len - 1 - 9 ) return 1;
    if ( pr_array[pattern[2]] !=  pattern_len - 1 -  9 ) return 1;
    if ( pr_array[pattern[3]] !=  pattern_len - 1 -  9 ) return 1;
    if ( pr_array[pattern[4]] !=  pattern_len - 1 -  7 ) return 1;

    free(pr_array);
    return 0;
}

int test_buffer_search() {
    char *buffer = "Hello world";
    char *pattern = "orld";
    int pattern_len = strlen(pattern);
    int buffer_len = strlen(buffer);
    uint32_t *pr_array = buffer_search_preproccess(pattern, pattern_len);

    uint32_t i = buffer_search(buffer, buffer_len, pattern, pattern_len, pr_array);

    return ! (i == 7);
}

int test_buffer_search_hex() {
    char *buffer = "\x12\x12\x34\x34\x56\x56\x78\x78\x9a\x9a\x34\xbc\xde\xde\xf0\xf0";
    char *pattern = "abc";
    int pattern_len = strlen(pattern);
    int buffer_len = strlen(buffer);
    uint32_t *pr_array = buffer_search_preproccess(pattern, pattern_len);

    int i = buffer_search(buffer, buffer_len, pattern, pattern_len, pr_array);

    return ! (i == -1);
}

int main(int argc, char** argv) {

    if (strcmp(argv[1], "buffer_search_preproccess") == 0 ) return test_buffer_search_preproccess();
    if (strcmp(argv[1], "buffer_search") == 0 ) return test_buffer_search();
    if (strcmp(argv[1], "buffer_search_hex") == 0 ) return test_buffer_search_hex();

}
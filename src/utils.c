#include "utils.h"

uint64_t get_file_size(char * file_path) {
    HANDLE hfile = CreateFile(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    LARGE_INTEGER size;

    if ( hfile == INVALID_HANDLE_VALUE) {
        perror("Error calculating the size of the file.");
        exit(1);
    }
    
    GetFileSizeEx(hfile, &size);
    CloseHandle(hfile);

    return size.QuadPart;
}
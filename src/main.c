#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void print_hex(FILE* fd, uint32_t column_size, uint32_t column_count, bool show_address) {
    unsigned char buff;
    int counter = 0;

    printf("%08x:\t", counter);
    while (!feof(fd))
    {
        buff = fgetc(fd);
        printf("%02x", buff);

        counter++;
        if ( counter % column_size == 0) printf(" ", counter);
        if ( counter % ((column_size)*column_count) == 0) {
            printf("\n");
            if ( !feof(fd) && show_address)
                printf("%08x:\t", counter);
        }
    }
    
}

int main(int argc, char const *argv[])
{
    
    FILE* f = fopen("./hex_dump.exe", "rb");
    print_hex(f, 3, 6, true);

    return 0;
}

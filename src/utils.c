#include "utils.h"

uint64_t get_file_size(char * file_path) {
    HANDLE hfile = CreateFile(file_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    LARGE_INTEGER size;

    if ( hfile == INVALID_HANDLE_VALUE) {
        perror("Error calculating the size of the file.\n");
        exit(1);
    }
    
    GetFileSizeEx(hfile, &size);
    CloseHandle(hfile);

    return size.QuadPart;
}

struct settings* init_settings() {
    struct settings* ptr_param = (struct settings*) malloc(sizeof(struct settings));

    assert(ptr_param != NULL);

    ptr_param->file_path = NULL;
    ptr_param->column_count = 10;
    ptr_param->column_size = 1;
    ptr_param->enable_address = true;
    ptr_param->enable_ascii = true;
    ptr_param->enable_color = true;
    ptr_param->number_type = D_HEXADECIMAL;

    return ptr_param;
}

void free_settings(struct settings* param) {
    if (param != NULL) free(param);
}

void print_settings(struct settings* param) {
    assert(param != NULL);
    printf("The current settings are:\n");
    printf("\tThe file path is %s\n", (param->file_path == NULL) ? "NULL" : param->file_path);
    printf("\tenable_color = %c\n", param->enable_color == true ? 't' : 'f');
    printf("\tenable_address = %c\n", param->enable_address == true ? 't' : 'f');
    printf("\tenable_ascii = %c\n", param->enable_ascii == true ? 't' : 'f');
    printf("\tcolumn_size = %u\n", param->column_size);
    printf("\tcolumn_count = %u\n", param->column_count);
    printf("\tnumber_type = %s\n", (param->number_type == D_HEXADECIMAL) ? "hex" : (param->number_type == D_BINARY) ? "bin" : "oct" );
}

void show_help() {
    printf("bhex: An other hex dumper with color support.\n");
    printf("Usage: hex_dump [-lbf] [-s n] [-c n] [-n hex|oct|bin] FILENAME\n");
    printf("\t-l: Don't show the address column.\n");
    printf("\t-b: Disable colors.\n");
    printf("\t-f: Disable ASCII column.\n");
    printf("\t-s n: Set the column size of n number.\n");
    printf("\t-c n: Set the column number to n.\n");
    printf("\t-n hex|oct|bin: Specify the dump type.\n");
    printf("\tFILENAME: a readable file.\n");
}



bool parse_arguments(int argc, char **argv, struct settings* params) {
    int c;
    bool status;

    while ( (c = getopt(argc, argv, "lbfs:c:n:h")) != -1 ) {
        switch(c) {
            case 'h':
                show_help();
                return false;
            case 'l':
                params->enable_address = false;
                break;
            case 'b':
                params->enable_color = false;
                break;
            case 'f':
                params->enable_ascii = false;
                break;
            case 's':
                params->column_size = str_to_posint32(optarg, &status);
                 if ( status == false )  {
                    perror("Invalid column size.\n");
                    return status;
                 }
                break;
            case 'c':
                 params->column_count = str_to_posint32(optarg, &status);
                 if ( status == false )  {
                    perror("Invalid column count.\n");
                    return status;
                 }
                 break;
            case 'n':
                if (strncmp(optarg, "bin", 4) == 0) {
                    params->number_type = D_BINARY;
                } else if (strncmp(optarg, "hex", 4) == 0) {
                    params->number_type = D_HEXADECIMAL;
                } else if (strncmp(optarg, "oct", 4) == 0) {
                    params->number_type = D_OCTAL;
                } else {
                    perror("Invalid number type.");
                    return false;
                }
                break;
            case '?':
                return false;
            default:
                return false;
        }
    }

    // printf("%d %d\n", optind, argc);

    if ( optind == argc ) {
        perror("Error: No file is specified, use -h to show the help.\n");
        return false;
    }  else if (argc - optind > 1) {
        perror("Error: Multiple files are specified.\n");
        return false;
    }

    params->file_path = argv[optind];
    

    return true;
}

uint32_t str_to_posint32(char *str, bool *status) {
    long int n;
    char *ptr;
    n = strtol(str, &ptr, 10);

    if ( ptr == str || n <= 0) {
        *status = false;
        return 0;
    }

    *status = true;
    return (uint32_t)n;

}

uint32_t digit_count(uint32_t base, int64_t number) {
    return floor( log2(_abs64(number))/log2(base) ) + 1;
}

bool enable_terminal_color() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }
    
    return true;
}
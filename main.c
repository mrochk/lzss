#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lzss.h"

#define USAGE                                               \
    {                                                       \
        fputs("Usage: lzss (-c|-d) <filename>.\n", stderr); \
        return EXIT_FAILURE;                                \
    }

int main(int argc, char* argv[]) {
    char *option, *filename;
    int   size;

    if (argc < 3) USAGE;

    option = argv[1], filename = argv[2];

    if (!strcmp(option, OPTION_COMPRESS)) {
        size = lzss_compress_file(filename);
        if (size == -1) {
            fputs("Error during file compression.", stderr);
            return EXIT_FAILURE;
        }
        printf("New compressed file size: %d bytes.\n", size);
    } else if (!strcmp(option, OPTION_DECODE)) {
        size = lzss_decode_file(filename);
        if (size == -1) {
            fputs("Error during file decoding.", stderr);
            return EXIT_FAILURE;
        }
        printf("New decoded file size: %d bytes.\n", size);
    } else {
        fputs("Invalid option provided.\n", stderr);
        USAGE;
    }

    return EXIT_SUCCESS;
}

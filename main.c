#include <stdio.h>
#include <stdlib.h>

#include "lzss.h"

int main() {
    char  x[1000]   = "abcdeabcdefabcdefgabcdefghabcdefghj\n";
    char  res[1000] = "";
    char* encode    = "input";
    char* decode    = "input.enc";

    lzss_encode_file(encode);
    lzss_decode_file(decode);

    lzss_encode(x, res);
    printf("res = %s\n", res);

    return EXIT_SUCCESS;
}
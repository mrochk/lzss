#include <stdio.h>
#include <stdlib.h>

#include "lzss.h"

int main() {
    char* encode = "input";
    char* decode = "input.enc";

    lzss_encode_file(encode);
    puts("File encoded.");

    lzss_decode_file(decode);
    puts("File decoded.");

    return 0;
}

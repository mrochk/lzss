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

    printf("input  size = %u bytes.\n", fsize_name(encode));
    printf("encoded size = %u bytes.\n", fsize_name(decode));

    return 0;
}

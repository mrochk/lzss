#include <stdio.h>
#include <stdlib.h>

#include "lzss.h"

int main() {
    char encode[] = "input", decode[] = "input.enc";
    uint _encode, _decode;

    lzss_encode_file(encode);
    puts("File encoded.");

    lzss_decode_file(decode);
    puts("File decoded.");

    _encode = fsize_name(encode), _decode = fsize_name(decode);
    printf("\nInput file size   = %u bytes.\n", _encode);
    printf("Encoded file size = %u bytes.\n", _decode);

    return EXIT_SUCCESS;
}

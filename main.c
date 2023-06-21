#include <stdio.h>
#include <stdlib.h>

#include "lzss.h"

int main() {
    char encode[] = "input", decode[] = "input.enc";
    int  _encode, _decode, difference;

    _encode    = lzss_encode_file(encode);
    _decode    = lzss_decode_file(decode);
    difference = _encode - _decode;

    printf("Input file size   = %u bytes.\n", _decode);
    printf("Encoded file size = %u  bytes.\n", _encode);
    printf("Difference        = %d bytes.\n", difference);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

#include "lzss.h"

int main() {
  char original[1000] = "repetitive repeat";
  char encoded[1000] = {'\0'};
  char decoded[1000] = {'\0'};

  lzss_encode(original, encoded);
  lzss_decode(encoded, decoded);

  printf("original = %s\n", original);
  printf("encoded  = %s\n", encoded);
  printf("decoded  = %s\n", decoded);

  return EXIT_SUCCESS;
}
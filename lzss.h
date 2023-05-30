#ifndef LZSS_H
#define LZSS_H

#define BUFFER_SIZE 15  // Must be greater than 0.
#define WINDOW_SIZE 30  // Must be greater than the size of the buffer.
#define BREAK_EVEN  1   // Minimum required subsequence size to be encoded.

extern void lzss_encode(char*, char*);

extern void lzss_decode(char*, char*);

#endif
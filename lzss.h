#ifndef LZSS_H
#define LZSS_H

#include <stdio.h>

typedef unsigned int uint;

/* Type used to represent the position of a subsequence in an array of
   characters.*/
typedef struct {
    int position;
    int length;
} SubCoord;

/* The size of the look-ahead buffer, that is, the consecutive subsequence
   we will look for in the window.
   Must be greater than 0. */
#define BUFFER_SIZE 1000

/* The size of the window where we search for repeated subsequences, (the
   longest subsequence of consecutives characters contained in the buffer).
   Must be greater than the size of the look-ahead buffer. */
#define WINDOW_SIZE 3000

/* How long must a subsequence be to be replaced by a dictionary
   reference ?
   Must be greater than 0. */
#define BREAK_EVEN 6

/* Byte used to indicate a dictionary reference. */
#define START_OF_REFERENCE_BYTE -0x66

/* Returns the size of the new encoded file. */
extern int lzss_encode_file(char *filename);

extern int lzss_decode_file(char *filename);

#endif
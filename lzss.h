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

/* The size of the look-ahead buffer, that is the subsequence we will look for
   in the window.
   Must be greater than 0. */
#define BUFFER_SIZE 1000

/* The size of the window where we search for repeated subsequences, (the
   longest subsequence of consecutives of characters contained in the buffer).
   Must be greater than the size of the look-ahead buffer. */
#define WINDOW_SIZE 3000

/* How long must a subsequence be to be replaced by the sequence of
   characters: "(pos|len)" ?
   Must be greater than 0. */
#define BREAK_EVEN 5

/* Byte used to indicate a dictionary reference. */
#define START_OF_REFERENCE_BYTE -0x66

extern void lzss_encode_file(char *filename);

extern void lzss_decode_file(char *filename);

extern uint fsize_file(FILE *file);

extern uint fsize_name(char *filename);

#endif
#ifndef LZSS_H
#define LZSS_H

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

#define OPTION_DECODE "-d"

#define OPTION_COMPRESS "-c"

/* Returns the size in bytes of the new compressed file. */
extern int lzss_compress_file(char *filename);

/* Returns the size in bytes of the new decoded file. */
extern int lzss_decode_file(char *filename);

#endif
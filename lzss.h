#ifndef LZSS_H
#define LZSS_H

/* The size of the look-ahead buffer, that is the subsequence we will look for
   in the window.
   Must be greater than 0. */
#define BUFFER_SIZE 15
/* The size of the window where we search for repeated subsequences, (the
   longest subsequence of consecutives of characters contained in the buffer).
   Must be greater than the size of the look-ahead buffer. */
#define WINDOW_SIZE 30
/* How long must a subsequence be to be replaced by the sequence of
   characters: "(pos|len)".
   Must be greater than 0. */
#define BREAK_EVEN 1

/* Encode src and put the result in dest, dest should be bigger than src in
   case the encoded version takes more place than the original (happens often if
   BREAK_EVEN < 8). */
extern void lzss_encode(char *src, char *dest);

/* Decode an array of characters encoded using lzss_encode and put
   the result in dest. */
extern void lzss_decode(char *src, char *dest);

#endif
# LZSS
Text compression & decompression program implementing the LZSS algorithm.

References:
- https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Storer%E2%80%93Szymanski
- https://youtu.be/EFUYNoFRHQI?t=323

The main functions are the following:
- `lzss_encode_file(char *filename)` to compress a file and create a new ".enc" binary file. 
- `lzss_decode_file(char *filename)` to decode a previously compressed ".enc" file and create a new ".dec" text file. 

To try them on the provided `input` text file just clone the project and type `make run`.

# LZSS
Text compression & decompression program implementing the LZSS algorithm.

References:
- https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Storer%E2%80%93Szymanski
- https://youtu.be/EFUYNoFRHQI?t=323

I chose the following structure for dictionary references: 
- "**START_OF_REFERENCE_BYTE** *(1 byte)* | **POSITION** *(2 bytes)* | **LENGTH** *(2 bytes)*"

You can modify the different constants used in the `lzss.h` header file and see how it affects the result and performance.

After compiling this program using `make`, to try this program on the provided `input` text file you can type `make test`.

To compress a file use the "-c" option, and use "-d" to decode a file previously encoded using **this** program in: `lzss (-c|-d) <filename>`.
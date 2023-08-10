# LZSS
Utility file compression & decompression program implementing the LZSS algorithm.

References:
- https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Storer%E2%80%93Szymanski
- https://youtu.be/EFUYNoFRHQI?t=323

I chose the following structure to encode dictionary references: 
| START OF REFERENCE BYTE | POSITION |  LENGTH |
|:-----------------------:|:--------:|:-------:|
|          1 byte         |  2 bytes | 2 bytes |

You can modify the different constants used in the `lzss.h` header file and see how it affects the result and performance.

After compiling this project by typing `make`, to try this program on the provided `input` text file you can type `make test`.

To compress a file, use the "**-c**" option, and use "**-d**" to decode a file previously encoded using **this** program.

Example: 
```
./lzss -c file.txt
```
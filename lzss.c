#include "lzss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int fsize(FILE *file) {
    unsigned int size;

    fseek(file, 0, SEEK_SET);
    fseek(file, 0, SEEK_END);
    size = (unsigned int)ftell(file);

    fseek(file, 0, SEEK_SET);
    return size;
}

static SubCoord make_subsequence_coord(int position, int length) {
    return (SubCoord){position, length};
}

static void get_subsequence(char *string, int from, int len, char *dest) {
    for (int i = from, _dest = 0; i < from + len; i++, _dest++)
        dest[_dest] = string[i];
}

static void shift(char *window, char *buffer, char *src, unsigned int *_src,
                  int n) {
    for (; n > 0; n--) {
        for (int i = 0; i < WINDOW_SIZE - 1; i++) window[i] = window[i + 1];
        window[WINDOW_SIZE - 1] = buffer[0];

        for (int i = 0; i < BUFFER_SIZE - 1; i++) buffer[i] = buffer[i + 1];
        buffer[BUFFER_SIZE - 1] = src[*_src];
        *_src                   = *_src + 1;
    }
}

static SubCoord longest_subsequence(char *window, char *buffer) {
    unsigned int length   = 0, len, _buf, _win;
    int          position = -1;

    for (int pos = 0; pos < WINDOW_SIZE; pos++) {
        len = _buf = 0, _win = pos;

        while ((_win <= WINDOW_SIZE && _buf <= BUFFER_SIZE) &&
               (window[_win] != '\0' && window[_win] == buffer[_buf]))
            len++, _win++, _buf++;

        if (len > length) position = pos, length = len;
    }

    return make_subsequence_coord(position, length);
}

extern int lzss_compress_file(char *filename) {
    char         encoded_filename[300]   = {'\0'};
    char         buffer[BUFFER_SIZE + 1] = {'\0'};
    char         window[WINDOW_SIZE + 1] = {'\0'};
    char *       text = NULL, c[2], c_, start = START_OF_REFERENCE_BYTE;
    unsigned int _src = BUFFER_SIZE, src_size, encoded_size;
    FILE *       src = NULL, *dest = NULL;
    short        position, length;
    SubCoord     sc;

    memset(window, '_', WINDOW_SIZE);

    strcat(encoded_filename, filename);
    strcat(encoded_filename, ".enc");

    src = fopen(filename, "r"), dest = fopen(encoded_filename, "wb");
    if (!src || !dest) return -1;

    src_size = fsize(src), text = (char *)calloc(src_size, sizeof(char));
    if (!text) return -1;

    fread(text, sizeof(char), src_size, src);
    strncat(buffer, text, BUFFER_SIZE);

    while (_src - BUFFER_SIZE < strlen(text)) {
        sc = longest_subsequence(window, buffer);

        if (sc.length < BREAK_EVEN) {
            sprintf(c, "%c", buffer[0]);
            c_ = c[0];

            fwrite(&c_, sizeof(c_), 1, dest);

            shift(window, buffer, text, &_src, 1);
        } else {
            position = WINDOW_SIZE - sc.position, length = sc.length;

            fwrite(&start, sizeof(start), 1, dest);
            fwrite(&position, sizeof(position), 1, dest);
            fwrite(&length, sizeof(length), 1, dest);

            shift(window, buffer, text, &_src, sc.length);
        }
    }

    encoded_size = fsize(dest);

    free(text);
    text = NULL;

    fclose(src);
    fclose(dest);

    printf("=> File \"%s\" compressed in \"%s\".\n", filename,
           encoded_filename);
    return (int)encoded_size;
}

extern int lzss_decode_file(char *filename) {
    char         decoded_filename[100] = {'\0'};
    char         buffer[BUFFER_SIZE]   = {'\0'};
    char         c, *text = NULL;
    FILE *       src = NULL, *dest = NULL;
    short        position, length;
    unsigned int src_size, decoded_size;

    strcat(decoded_filename, filename);
    strcat(decoded_filename, ".dec");

    src = fopen(filename, "rb"), dest = fopen(decoded_filename, "w");
    if (!src || !dest) return -1;

    src_size = fsize(src), text = (char *)(calloc(src_size * 2, sizeof(char)));
    if (!text) return -1;

    while (fread(&c, sizeof(char), 1, src)) {
        memset(buffer, '\0', BUFFER_SIZE);

        if (c != START_OF_REFERENCE_BYTE) {
            sprintf(buffer, "%c", c);
        } else {
            fread(&position, sizeof(position), 1, src);
            fread(&length, sizeof(length), 1, src);

            get_subsequence(text, strlen(text) - position, length, buffer);
        }

        strcat(text, buffer);
    }

    fwrite(text, strlen(text), 1, dest);

    decoded_size = fsize(dest);

    free(text);
    text = NULL;

    fclose(src);
    fclose(dest);

    printf("=> File \"%s\" decoded in \"%s\".\n", filename, decoded_filename);
    return (int)decoded_size;
}

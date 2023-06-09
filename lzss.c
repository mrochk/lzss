#include "lzss.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int position;
    int length;
} SubCoord;

static SubCoord make_subsequence_coord(int position, int length) {
    return (SubCoord){position, length};
}

static void get_subsequence(char *string, int from, int len, char *dest) {
    for (int i = from, _dest = 0; i < from + len; i++, _dest++)
        dest[_dest] = string[i];
}

static SubCoord get_subsequence_coord(char *coordinates) {
    int  position, length;
    char c, c_, c__;

    sscanf(coordinates, "%c %d %c %d %c", &c, &position, &c_, &length, &c__);
    return make_subsequence_coord(position, length);
}

static int ndigits(int num) { return 1 + (int)log10((double)num); }

static void shift(char *window, char *buffer, char *src, int *_src, int n) {
    for (; n > 0; n--) {
        for (int i = 0; i < WINDOW_SIZE - 1; i++) window[i] = window[i + 1];
        window[WINDOW_SIZE - 1] = buffer[0];

        for (int i = 0; i < BUFFER_SIZE - 1; i++) buffer[i] = buffer[i + 1];
        buffer[BUFFER_SIZE - 1] = src[*_src];
        *_src                   = *_src + 1;
    }
}

static SubCoord longest_subsequence(char *window, char *buffer) {
    int length = 0, position = -1, pos, len, _buf, _win;

    for (pos = 0; pos < WINDOW_SIZE; pos++) {
        len = 0, _buf = 0, _win = pos;

        while ((_win < WINDOW_SIZE && _buf < BUFFER_SIZE) &&
               (window[_win] != '\0' && window[_win] == buffer[_buf])) {
            len++, _win++, _buf++;
        }

        if (len > length) {
            position = pos;
            length   = len;
        }
    }

    return make_subsequence_coord(position, length);
}

extern void lzss_encode_string(char *src, char *dest) {
    char   window[WINDOW_SIZE + 1], buffer[BUFFER_SIZE + 1] = {'\0'};
    int    _src    = BUFFER_SIZE;
    size_t len_src = strlen(src);

    memset(window, '_', WINDOW_SIZE);
    strncat(buffer, src, BUFFER_SIZE);

    while (_src - BUFFER_SIZE < len_src) {
        SubCoord sc      = longest_subsequence(window, buffer);
        char     buf[20] = {'\0'};

        if (sc.length < BREAK_EVEN) {
            sprintf(buf, "%c", buffer[0]);
            shift(window, buffer, src, &_src, 1);
        } else {
            sprintf(buf, "(%d|%d)", WINDOW_SIZE - sc.position, sc.length);
            shift(window, buffer, src, &_src, sc.length);
        }

        strcat(dest, buf);
    }
}

extern void lzss_decode_string(char *src, char *dest) {
    for (int i = 0; src[i] != '\0'; i++) {
        char buf[300] = {'\0'};

        if (src[i] != '(') {
            sprintf(buf, "%c", src[i]);
        } else {
            char coord[30] = {'\0'};

            get_subsequence(src, i, 9, coord);
            SubCoord sc = get_subsequence_coord(coord);

            get_subsequence(dest, strlen(dest) - sc.position, sc.length, buf);

            i += (2 + ndigits(sc.position) + ndigits(sc.length));
        }

        strcat(dest, buf);
    }
}

extern void lzss_encode_file(char *filename) {
    char encoded_filename[100] = {'\0'};
    strcat(encoded_filename, filename);
    strcat(encoded_filename, ".enc");

    FILE *src  = fopen(filename, "r");
    FILE *dest = fopen(encoded_filename, "wb");

    int  _src                    = BUFFER_SIZE;
    char buffer[BUFFER_SIZE + 1] = {'\0'};
    char window[WINDOW_SIZE + 1] = {'\0'};
    memset(window, '_', WINDOW_SIZE);

    fseek(src, 0L, SEEK_END);
    long src_size = ftell(src);
    fseek(src, 0L, SEEK_SET);
    char *text = (char *)calloc(src_size, sizeof(char));
    fread(text, sizeof(char), src_size, src);
    strncat(buffer, text, BUFFER_SIZE);

    while (_src - BUFFER_SIZE < strlen(text)) {
        SubCoord sc = longest_subsequence(window, buffer);
        if (sc.length < BREAK_EVEN) {
            char c[2] = {'\0'}, c_;
            sprintf(c, "%c", buffer[0]);
            c_ = c[0];
            fwrite(&c_, sizeof(c_), 1, dest);
            shift(window, buffer, text, &_src, 1);
        } else {
            char  start    = START_OF_REFERENCE_BYTE;
            short position = WINDOW_SIZE - sc.position, length = sc.length;

            fwrite(&start, sizeof(start), 1, dest);
            fwrite(&position, sizeof(position), 1, dest);
            fwrite(&length, sizeof(length), 1, dest);

            shift(window, buffer, text, &_src, sc.length);
        }
    }
    free(text);
    fclose(src);
    fclose(dest);
}

extern void lzss_decode_file(char *filename) {
    char decoded_filename[100] = {'\0'};
    strcat(decoded_filename, filename);
    strcat(decoded_filename, ".dec");

    FILE *src  = fopen(filename, "rb");
    FILE *dest = fopen(decoded_filename, "w");

    fseek(src, 0L, SEEK_END);
    long src_size = ftell(src);
    fseek(src, 0L, SEEK_SET);

    char *test = (char *)(calloc(src_size * 2, sizeof(char)));

    while (1) {
        char buffer[300] = {'\0'}, c;

        if (!fread(&c, sizeof(char), 1, src)) break;

        if (c != START_OF_REFERENCE_BYTE) {
            sprintf(buffer, "%c", c);
        } else {
            short position, length;
            fread(&position, sizeof(position), 1, src);
            fread(&length, sizeof(position), 1, src);
            get_subsequence(test, strlen(test) - position, length, buffer);
        }
        strcat(test, buffer);
    }
    fwrite(test, strlen(test), 1, dest);

    free(test);
    fclose(src);
    fclose(dest);
}

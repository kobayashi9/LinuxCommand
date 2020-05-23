#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

char *fname;
int nlines = 0;
int nwords = 0;
int rd_size = 0;

bool rerror(FILE *fp) {
    if (fp == NULL) {
        fprintf(stderr, "wc: %s: No such file or directory\n", fname);
        return true;
    }
    return false;
}

bool ischar(char c) {
    if ('!' <= c && c <= '~') {
        return true;
    }
    return false;
}

void wc(FILE *fp, char *fname) {
    char buf[2048];
    size_t ret;
    bool inword = false;
    while (ret = fread(buf, 1, sizeof(buf), fp)) {
        rd_size += ret;
        for (int i = 0; i < ret; i++) {
            if (inword && !ischar(buf[i])) {
                inword = false;
            } else if (!inword && ischar(buf[i])) {
                nwords++;
                inword = true;
            }
            if (buf[i] == '\n') {
                nlines++;
            }
        }
    }
    printf("% 4d % 4d %d %s\n", nlines, nwords, rd_size, fname);
}

int main(int argc, char **argv) {
    FILE *fp;
    for (int i = 1; i < argc; i++) {
        fname = argv[i];
        fp = fopen(fname, "r");
        if (rerror(fp)){
            continue;
        }
        wc(fp, fname);
    }
}
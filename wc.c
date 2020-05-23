#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

char *fname;

void oprror(int fd) {
    if (fd < 0) {
        fprintf(stderr, "wc: %s: No such file or directory\n", fname);
        exit(1);
    }
}

bool ischar(char c) {
    if ('!' <= c && c <= '~') {
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    FILE *fp;
    char buf[2048];
    int nlines = 0;
    int nwords = 0;
    size_t ret;
    size_t rd_size = 0;
    bool inword = false;
    argv++;
    fname = *argv;
    fp = fopen(fname, "r");

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
    printf("% 4d % 4d %ld %s\n", nlines, nwords, rd_size, fname);
}
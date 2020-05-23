#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fname;

void rerror(FILE *fp) {
    if (fp == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", fname);
        fclose(fp);
        exit(1);
    }
}

int main(int argc, char **argv) {
    FILE *fp;
    int buf = 256;
    char str[buf];
    argv++;
    while (*argv == NULL) {
        scanf("%s", str);
        if (strcmp(str, "\\D") == 0) {
            return 0;
        }
        printf("%s\n", str);
    }
    for (; *argv != NULL; argv++) {
        fname = *argv;
        fp = fopen(fname, "r");
        rerror(fp);

        while ((fgets(str, buf, fp)) != NULL) {
            printf("%s", str);
        }
        fclose(fp);
    }
}

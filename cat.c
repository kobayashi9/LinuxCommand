#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    char *fname = argv[1];
    fp = fopen(fname, "r");
    int chr;
    int buf = 256;
    char str[buf];
    while (fname == NULL) {
        scanf("%s", str);
        if (strcmp(str, "\\D") == 0) {
            return 0;
        }
        printf("%s\n", str);
    }

    if (fp == NULL) {
        printf("cat: %s: No such file or directory\n", fname);
        return -1;
    }

    while ((fgets(str, buf, fp)) != NULL) {
        printf("%s", str);
    }
    printf("\n");
    fclose(fp);
}
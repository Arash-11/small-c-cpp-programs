#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_SIZE 256

int main(int argc, char *argv[]) {
    if (argc < 2)
        exit(0);

    char str[MAX_STR_SIZE];

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror("wcat: cannot open file\n");
            exit(1);
        }

        while (fgets(str, sizeof(str), fp) != NULL)
            printf("%s", str);
    }

    return 0;
}

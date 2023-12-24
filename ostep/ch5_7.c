#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        fprintf(stdout, "[child] printing to stdout should NOT work\n");
        fprintf(stderr, "[child] printing to stderr should work\n");
    } else {
        printf("[parent] this should print fine\n");
    }

    return 0;
}

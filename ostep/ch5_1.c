#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 100;

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc > 0) {
        printf("Value of x in parent process (pid:%d): %d\n", (int) getpid(), x);
        x = 50;
    } else {
        printf("Value of x in child process (pid:%d): %d\n", (int) getpid(), x);
        x = 11;
    }

    printf("Value of x in main process (pid:%d): %d\n", (int) getpid(), x);

    return 0;
}

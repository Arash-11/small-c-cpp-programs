#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("./ch5_test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd == -1) {
        perror("failed to open file\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        perror("fork failed\n");
        exit(1);
    } else if (rc > 0) {
        char buf[] = "Hello from parent!\n";
        printf("[parent process] file descriptor: %d\n", fd);
        write(fd, buf, strlen(buf));
    } else {
        char buf[] = "Hi from child!\n";
        printf("[child process] file descriptor: %d\n", fd);
        write(fd, buf, strlen(buf));
    }

    return 0;
}

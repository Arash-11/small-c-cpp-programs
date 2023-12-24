#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int fd;
char *buf;

void sigchld_handler(int signum) {
    write(fd, buf, strlen(buf));
    exit(0);
}

int main() {
    fd = open("./ch5_test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd == -1) {
        perror("failed to open file\n");
        exit(1);
    }

    // set up signal handler before fork to avoid race condition
    signal(SIGCHLD, sigchld_handler);

    int rc = fork();
    if (rc < 0) {
        perror("fork failed\n");
        exit(1);
    } else if (rc > 0) {
        buf = "goodbye\n";
        pause(); // Wait for signal
    } else {
        char child_buf[] = "hello\n";
        write(fd, child_buf, strlen(child_buf));
        exit(0); // child process exits; triggers SIGCHLD
    }

    return 0;
}

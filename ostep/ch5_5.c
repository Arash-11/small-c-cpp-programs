#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int rc = fork();
    int rc_wait = wait(NULL);

    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        int rc_child = fork();
        int rc_child_wait = wait(NULL);

        if (rc_child < 0) {
            perror("fork failed");
            exit(1);
        } else if (rc_child == 0) {
            printf("[child child] rc_wait: %d\n", rc_wait);
            printf("[child child] pid: %d\n", (int) getpid());
            printf("[child child] rc_child_wait: %d\n", rc_child_wait);
        } else {
            printf("[child] rc_wait: %d\n", rc_wait);
            printf("[child] pid: %d\n", (int) getpid());
            printf("[child] rc_child: %d\n", rc_child);
            printf("[child] rc_child_wait: %d\n", rc_child_wait);
        }
    } else {
        printf("[parent] pid: %d\n", (int) getpid());
        printf("[parent] rc_wait: %d\n", rc_wait);
    }

    return 0;
}

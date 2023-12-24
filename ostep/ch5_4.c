#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc == 0) {
        char *args[] = {"ls", NULL};
        // int result = execl("/bin/ls", args[0], args[1]);
        // int result = execle("/bin/ls", args[0], args[1]);
        // int result = execlp(args[0], args[0], args[1]);
        // int result = execv("/bin/ls", args);
        // int result = execve("/bin/ls", args, NULL);
        int result = execvp(args[0], args);

        if (result == -1) {
            perror("Failed to execute command in child process");
            exit(1);
        }
    } else {
        // do nothing in the parent process
    }

    return 0;
}

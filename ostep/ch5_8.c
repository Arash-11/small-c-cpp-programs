#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run(char *cmd) {
    char *args[] = {cmd, NULL};
    execvp(cmd, args);
    exit(1); // Exit the child process in case of exec() failure
}

int main() {
    /*
        To set up a communication channel between two processes,
        the pipe must exist before the child processes are created.
        That's why the pipe is created before forking -- after forking,
        both child processes inherit these file descriptors, allowing
        them to communicate through the pipe.
    */

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        exit(1);
    }

    /*
        dup2() works by manipulating the kernel's file descriptor table
        to make one file descriptor a duplicate of another, not just by
        copying an integer value, but by altering the underlying references
        in the system's file management structures.
    */

    int pid_1 = fork();
    if (pid_1 == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid_1 == 0) {
        close(pipefd[0]); // close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // close original write end
        run("ls");
    }

    int pid_2 = fork();
    if (pid_2 == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid_2 == 0) {
        close(pipefd[1]); // close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(pipefd[0]); // close original read end
        run("sort");
    }

    /*
        Closing the pipe's file descriptors in the parent process before
        waiting for the child processes ensures that the pipe is used
        correctly and that the child processes can complete their tasks
        without interference or deadlock.
    */

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);

    return 0;
}

/*
- Process A (main) forks Process B
- Process B forks Process C
- Process B kills itself
- Process C forks Process D
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    printf("[Process A] pid:%d, parent pid:%d\n", (int) getpid(), (int) getppid());

    int rc_b = fork();
    if (rc_b > 0) {
        // Process A
        printf("[Process A] parent of Process B (pid:%d) \n", rc_b);
        wait(NULL); // optionally wait for Process B
    } else {
        // Process B
        printf("[Process B] pid:%d, parent pid:%d\n", (int) getpid(), (int) getppid());

        int rc_c = fork();
        if (rc_c > 0) {
            // Still in Process B
            printf("[Process B] parent of Process C (pid:%d)\n", rc_c);
            printf("Killing Process B (pid:%d) \n", (int) getpid());
            kill(getpid(), SIGKILL); // Kill Process B
        } else {
            // Process C
            sleep(1); // Wait for Process B to die to ensure the correct PIDs get printed out
            printf("\n[Process C] pid:%d, parent pid:%d\n", (int) getpid(), (int) getppid());

            int rc_d = fork();
            if (rc_d > 0) {
                // Still in Process C
                printf("[Process C] parent of Process D (pid:%d)\n", rc_d);
                sleep(1); // Keep Process C alive for a bit so Process D prints out its PID
            } else {
                // Process D
                printf("[Process D] pid:%d, parent pid:%d\n", (int) getpid(), (int) getppid());
            }
        }
    }

    return 0;
}

/*
WHEN NOT KILLING PROCESS B (lines 29, 30, 33 commented)
--------------------------------------------------------------
[Process A] pid:20296, parent pid:14697
[Process A] parent of Process B (pid:20297) 
[Process B] pid:20297, parent pid:20296
[Process B] parent of Process C (pid:20298)
[Process C] pid:20298, parent pid:20297
[Process C] parent of Process D (pid:20299)
[Process D] pid:20299, parent pid:20298
--------------------------------------------------------------
Process A
    |__ Process B
            |__ Process C
                    |__ Process D
--------------------------------------------------------------


WHEN KILLING PROCESS B
--------------------------------------------------------------
[Process A] pid:27561, parent pid:23517
[Process A] parent of Process B (pid:27567) 
[Process B] pid:27567, parent pid:27561
[Process B] parent of Process C (pid:27568)
Killing Process B (pid:27567) 
➜  ostep git:(main) ✗ 
[Process C] pid:27568, parent pid:1
[Process C] parent of Process D (pid:27590)
[Process D] pid:27590, parent pid:27568

➜  ostep git:(main) ✗ 
--------------------------------------------------------------
Process A
Process C
    |__ Process D
--------------------------------------------------------------
*/

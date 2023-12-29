/*
    This program measures the time it takes for
    a syscall, using 0-byte reads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct timeval tv;

tv getcurrenttime() {
    tv timeval;
    if (gettimeofday(&timeval, NULL) == -1) {
        perror("gettimeofday");
        exit(1);
    }
    return timeval;
}

long get_time_diff_microsecs(tv start, tv end) {
    long seconds = end.tv_sec - start.tv_sec;
    long microsecs = end.tv_usec - start.tv_usec;
    return seconds * 1000000 + microsecs;
}

int main() {
    int fd = open("./ch6_test.txt", O_CREAT | O_RDONLY, S_IRUSR);
    if (fd == -1) {
        perror("Could not open file");
        exit(1);
    }

    int i = 100;
    while (i--) {
        tv start = getcurrenttime();
        read(fd, NULL, 0); /* intentionally not checking for errors */
        tv end = getcurrenttime();

        long time_diff = get_time_diff_microsecs(start, end);

        printf("time_diff: %ld microseconds\n", time_diff);
    }

    close(fd);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int get_num_length(long num) {
    int len = 1;

    for (int i = 10; num / i > 0; i *= 10)
        len++;

    return len;
}

bool is_armstrong_number(long num) {
    int len = get_num_length(num);
    long sum = 0;
    long tmp = num;

    while (tmp > 0) {
        int digit = tmp % 10;
        long raised = (long) pow(digit, len);
        sum += raised;
        tmp /= 10;
    }

    return sum == num;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("You should supply one argument of type long int.");
        exit(EXIT_FAILURE);
    }

    long num = strtol(argv[1], NULL, 10);

    printf("Is %lu an Armstrong number? %s\n", num, is_armstrong_number(num) ? "True" : "False");

    return 0;
}

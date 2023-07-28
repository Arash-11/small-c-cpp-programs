#include <stdio.h>
#include <ctype.h>
#include "stack.h"

int process_expression(void);

int main(void) {
    while (true) {
        printf("Enter an RPN expression: ");
        printf("Value of expression: %d\n\n", process_expression());
    }

    return 0;
}

int process_expression(void) {
    char ch;
    int result;

    do {
        scanf("%c", &ch);

        if (isdigit(ch)) {
            push(ch - '0');
        } else if (ch == '+') {
            push(pop() + pop());
        } else if (ch == '-') {
            int num_second = pop();
            int num_first = pop();
            push(num_first - num_second);
        } else if (ch == '*') {
            push(pop() * pop());
        } else if (ch == '/') {
            int num_second = pop();
            int num_first = pop();
            push(num_first / num_second);
        } else if (ch == '=') {
            result = pop();
            clear_stack();
        }
    } while (ch != '\n');

    return result;
}

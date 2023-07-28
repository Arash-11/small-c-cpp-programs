#include <stdbool.h>
#include <stdio.h>

#define STACK_SIZE 100

int stack[STACK_SIZE];
int top = 0;

void clear_stack(void) {
    top = 0;
}

bool is_empty(void) {
    return top == 0;
}

bool is_full(void) {
    return top == STACK_SIZE;
}

void push(int i) {
    if (is_full()) {
        printf("Error: Stack overflow\n");
    } else {
        stack[top++] = i;
    }
}

int pop(void) {
    if (is_empty()) {
        printf("Error: Stack underflow\n");
        return 0;
    } else {
        int num = stack[top - 1];
        stack[--top] = 0;
        return num;
    }
}

#include <stdbool.h>

#define STACK_SIZE 100

extern int stack[STACK_SIZE];

extern int top;

void clear_stack(void);

bool is_empty(void);

bool is_full(void);

void push(int i);

int pop(void);

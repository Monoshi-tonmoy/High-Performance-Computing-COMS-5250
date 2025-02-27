#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int Peek(StackFrame* top) {
    if (!top) {
        printf("Stack is empty!\n");
        return 0;
    }
    printf("Current function: %s\n", top->function_name);
    return 1;
}
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void DisplayStack(StackFrame* top) {
    // Input: Top reference of the stackframe
    // Checks if the top is NULL, that means the stack is empty
    // Else calls PrintNode to print the function call stack
    if (!top) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Function Call Stack:\n2");
    PrintNode(top);
}

void PrintNode(StackFrame* top) {
    //Input: top reference pointer of the stack
    // Print the function name, arguments of the function at the top of the stack
    if (!top) return;
    printf("Function: %s (", top->function_name);
    for (int i = 0; i < top->arg_count; i++) {
        printf("%s", top->arguments[i]);
        if (i < top->arg_count - 1) printf(", ");
    }
    printf(")\n");
    PrintNode(top->next);
}
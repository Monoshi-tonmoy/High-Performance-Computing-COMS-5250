#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void GetStackSize(StackFrame* top, int* stack_size) {
    //input: Stack top reference pointer and stack size
    int count = 0;
    StackFrame* temp = top;
    while (temp) {
        count++;
        temp = temp->next;
    }
    *stack_size = count;
}

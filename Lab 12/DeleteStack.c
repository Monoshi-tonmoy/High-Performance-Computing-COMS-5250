#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void DeleteStack(StackFrame** top) {
    //Takes the top of the stack and frees up the stack
    StackFrame* temp;
    while (*top) {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

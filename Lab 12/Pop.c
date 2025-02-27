#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


void Pop(StackFrame** top, char* function_name) {
    // Input: Stack Top 
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    StackFrame* temp = *top;
    strcpy(function_name, temp->function_name);
    *top = temp->next;
    free(temp);
    printf("Returning from function: %s\n", function_name);
}
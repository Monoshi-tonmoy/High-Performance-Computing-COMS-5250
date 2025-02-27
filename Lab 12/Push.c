#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


void Push(StackFrame** top) {
    //Input: Takes the top of the stack
    // Takes the function information from the user
    //Pushes a new function node frame as the top of the stack

    StackFrame* new_frame = (StackFrame*)malloc(sizeof(StackFrame));
    if (!new_frame) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter function name: ");
    scanf("%s", new_frame->function_name);
    printf("Enter number of arguments: ");
    scanf("%d", &new_frame->arg_count);
    for (int i = 0; i < new_frame->arg_count; i++) {
        printf("Enter argument %d: ", i + 1);
        scanf("%s", new_frame->arguments[i]);
    }
    new_frame->next = *top;
    *top = new_frame;
}
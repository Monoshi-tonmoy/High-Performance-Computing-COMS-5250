#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


int QueryOption() {
    //This function takes user input for making a stack operation choice
    int option;
    printf("Enter choice: ");
    scanf("%d", &option);
    return option;
}

void ExecuteOption(const int option, StackFrame** top) {
    // input: User option and Stack top pointer
    //This function takes the user option for stack operation and the top of the stack for operation.
    char function_name[MAX_NAME];
    switch (option) {
        case 1:
            Push(top);
            break;
        case 2:
            Pop(top, function_name);
            break;
        case 3:
            Peek(*top);
            break;
        case 4:
            DisplayStack(*top);
            break;
        case 5: {
            int size;
            GetStackSize(*top, &size);
            printf("Stack size: %d\n", size);
            break;
        }
        case 6:
            DeleteStack(top);
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Try again.\n");
    }
}

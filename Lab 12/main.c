#include "stack.h"

int main() {
    // Function to prompt the user to use a stack
    StackFrame* top = NULL;
    int option;
    
    do {
        DisplayOptions();
        option = QueryOption();
        ExecuteOption(option, &top);
    } while (option != 6);
    
    return 0;
}
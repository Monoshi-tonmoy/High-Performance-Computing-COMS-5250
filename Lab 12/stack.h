#ifndef __stack_H__
#define __stack_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 5  
#define MAX_NAME 50 

// This structure is for function name, function arguments, and each function has how many arguments
typedef struct StackFrame {
    char function_name[MAX_NAME];
    char arguments[MAX_ARGS][MAX_NAME];
    int arg_count;
    struct StackFrame* next;
} StackFrame;

// Defininig the function definitions
void DisplayOptions();
int QueryOption();
void ExecuteOption(const int option, StackFrame** Top);
void Push();
void Pop(StackFrame** top, char* function_name);
int Peek(StackFrame* top);
void DisplayStack(StackFrame* top);
void PrintNode(StackFrame* top);
void GetStackSize(StackFrame* top, int* stack_size);
void DeleteStack(StackFrame** top);


#endif

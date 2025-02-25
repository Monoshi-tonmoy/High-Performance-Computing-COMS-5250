// Defining the header for linked list with character value
#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define node structure with char instead of int
typedef struct node {
    int position;
    char value;
    struct node* next;
} node;

// Function prototypes by following class lecture slides
int GetNumberOfNodes();
void GenerateList(node** head, const int num);
void Print(const int forward, const node* head);
void PrintList(const node* head);
void ReversePrintList(const node* head);
char GetKey();
void SearchList(const node* head, char key);
void DeleteList(node** head);

#endif

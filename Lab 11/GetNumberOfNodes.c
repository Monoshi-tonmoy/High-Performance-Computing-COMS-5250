#include "node.h"

//Following class lecure slides
int GetNumberOfNodes() {
    int num;
    printf("Enter the number of nodes: ");
    while (scanf("%d", &num) != 1 || num <= 0) {
        printf("Invalid input. Enter a positive integer: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    return num;
}
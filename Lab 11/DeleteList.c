#include "node.h"

//Following class lecure slides
void DeleteList(node** head) {
    node* temp;
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
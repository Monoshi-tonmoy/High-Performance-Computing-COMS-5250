#include "node.h"

//Following class lecure slides
void Print(const int forward, const node* head) {
    if (!head) {
        printf("List is empty.\n\n");
        return;
    }
    printf("\n--------------------------\n");
    printf("| Pos | Val | Address   |\n");
    printf("--------------------------\n");
    if (forward) PrintList(head);
    else ReversePrintList(head);
    printf("--------------------------\n");
}

void PrintList(const node* head) {
    if (!head) return;
    printf("| %3d | %3c | %p |\n", head->position, head->value, head);
    PrintList(head->next);
}

void ReversePrintList(const node* head) {
    if (!head) return;
    ReversePrintList(head->next);
    printf("| %3d | %3c | %p |\n", head->position, head->value, head);
}
#include "node.h"


void GenerateList(node** head, const int num_nodes) {
    node* temp;
    srand(time(NULL));

    for (int i = 0; i < num_nodes; i++) {
        temp = (node*)malloc(sizeof(node));
        
       // Based on the 0 or 1 value of is_upper, which is generated randomly, we are selecting either uppercase or lowercase character
        int is_upper = rand() % 2;
        temp->value = is_upper ? ('A' + rand() % 26) : ('a' + rand() % 26);
        
        temp->position = 0;
        printf("%c ", temp->value);

        if (*head == NULL) {
            *head = temp;
            (*head)->next = NULL;
        } else {
            temp->next = *head;
            *head = temp;
        }
    }
    
    printf("\n");
    node* ptr = *head;
    int pos = 1;
    while (ptr != NULL) {
        ptr->position = pos++;
        ptr = ptr->next;
    }
}

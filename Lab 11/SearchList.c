#include "node.h"

//Following class lecure slides
void SearchList(const node* head, char key) {
    int flag = 0; //flag to check if the value is found or not
    while (head) {
        if (head->value == key){
            printf("Found '%c' at Position: %d\n", key, head->position);
            flag = 1;
        }
        head = head->next;
    }
    if(flag == 0){
        printf("Value is not found\n");
    }
}
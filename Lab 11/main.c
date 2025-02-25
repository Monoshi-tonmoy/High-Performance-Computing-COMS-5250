#include "node.h"

//Following class lecure slides
int main() {
    node* head = NULL;
    const int num_nodes = GetNumberOfNodes();
    GenerateList(&head, num_nodes);
    Print(1, head);
    Print(0, head);
    
    if (num_nodes > 0) {
        char key = GetKey();
        SearchList(head, key);
    }
    
    DeleteList(&head);
    return 0;
}
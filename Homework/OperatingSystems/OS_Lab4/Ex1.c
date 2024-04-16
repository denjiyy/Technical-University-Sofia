#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* lastNode = *headRef;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
}

void display(struct Node* head) {
    struct Node* temp = head;
    printf("Data entered in the list:\n");
    while (temp != NULL) {
        printf("Data = %d\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    int numNodes, data;
    struct Node* head = NULL;

    printf("Input the number of nodes: ");
    scanf_s("%d", &numNodes);

    for (int i = 0; i < numNodes; i++) {
        printf("Input data for node %d: ", i + 1);
        scanf_s("%d", &data);
        append(&head, data);
    }

    display(head);

    return 0;
}
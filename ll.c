#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

// Function to add a new node
void addNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

// Function to delete a particular node by location
void deleteNodeByLocation(int location) {
    if (head == NULL) return;
    
    Node* temp = head;
    if (location == 0) {
        head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < location - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return;

    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

// Function to delete all nodes containing a particular data
void deleteNodesByData(int data) {
    Node *temp = head, *prev = NULL;
    while (temp != NULL && temp->data == data) {
        head = temp->next;
        free(temp);
        temp = head;
    }

    while (temp != NULL) {
        while (temp != NULL && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

// Function to delete the entire linked list
void deleteList() {
    Node* temp = head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    head = NULL;
}

// Function to display the linked list
void displayList() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to display the inverted linked list
void displayInvertedList() {
    void printReverse(Node* node) {
        if (node == NULL) return;
        printReverse(node->next);
        printf("%d -> ", node->data);
    }
    printReverse(head);
    printf("NULL\n");
}

// Function to display the total memory space occupied by the linked list
void displayMemorySpace() {
    Node* temp = head;
    size_t totalSize = 0;
    while (temp != NULL) {
        totalSize += sizeof(Node);
        temp = temp->next;
    }
    printf("Total memory space occupied by the linked list: %zu bytes\n", totalSize);
}

// Function to delete nodes containing a particular data and the next subsequent node
void deleteNodesAndNextByData(int data) {
    Node *temp = head, *prev = NULL;
    while (temp != NULL && temp->data == data) {
        head = temp->next;
        free(temp);
        temp = head;
    }

    while (temp != NULL) {
        while (temp != NULL && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
        if (temp != NULL) {
            prev->next = temp->next;
            free(temp);
            temp = prev->next;
        }
    }
}

// Main function to test the linked list operations
int main() {
    addNode(1);
    addNode(5);
    addNode(3);
    addNode(5);
    addNode(2);
    addNode(5);

    printf("Original List: ");
    displayList();

    printf("Inverted List: ");
    displayInvertedList();

    printf("Memory Space: ");
    displayMemorySpace();

    deleteNodeByLocation(2);
    printf("After deleting node at location 2: ");
    displayList();

    deleteNodesByData(5);
    printf("After deleting nodes with data 5: ");
    displayList();

    deleteNodesAndNextByData(3);
    printf("After deleting nodes with data 3 and its next node: ");
    displayList();

    deleteList();
    printf("After deleting the entire list: ");
    displayList();

    return 0;
}

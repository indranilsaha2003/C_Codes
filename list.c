#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* append(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return head;
}

Node* insertAtPosition(Node* head, int data, int position) {
    Node* newNode = createNode(data);
    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        for (int i = 0; i < position - 1; ++i) {
            if (current == NULL) {
                printf("Invalid position\n");
                return head;
            }
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

Node* deleteNode(Node* head, int data) {
    if (head == NULL) {
        printf("List is empty\n");
        return head;
    }
    if (head->data == data) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node* current = head;
    while (current->next != NULL) {
        if (current->next->data == data) {
            Node* temp = current->next;
            
            current->next = temp->next;
            free(temp);
            return head;
        }
        current = current->next;
    }
    printf("Element not found\n");
    return head;
}

void display(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    int choice, data, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create the list\n");
        printf("2. Insert element at position\n");
        printf("3. Delete element\n");
        printf("4. Display list\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements: ");
                int n;
                scanf("%d", &n);
                for (int i = 0; i < n; ++i) {
                    printf("Enter element: ");
                    scanf("%d", &data);
                    head = append(head, data);
                }
                break;
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                head = insertAtPosition(head, data, position);
                break;
            case 3:
                printf("Enter element to delete: ");
                scanf("%d", &data);
                head = deleteNode(head, data);
                break;
            case 4:
                display(head);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
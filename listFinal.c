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
void insertAtFront(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void insertAtPosition(struct Node** head, int value, int position) {
    if (position <= 0) {
        printf("Invalid position!\n");
        return;
    }
    if (position == 1) {
        insertAtFront(head, value);
        return;
    }
    struct Node* newNode = createNode(value);
    struct Node* temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; ++i) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// void insertAfterNodeValue(struct Node** head, int targetValue, int data) {
//     struct Node* newNode = createNode(data);
//     struct Node* current = *head;

//     while (current != NULL) {
//         if (current->data == targetValue) {
//             newNode->next = current->next;
//             current->next = newNode;
//             break;
//         }
//         current = current->next;
//     }
//     if (current == NULL) {
//         printf("Node with target value not found.\n");
//         free(newNode);
//     }
// }
void deleteAtFront(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}
void deleteAtEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    struct Node* current = *head;
    struct Node* previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    free(current);
    previous->next = NULL;
}

void deleteAtPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    if (position <= 0) {
        printf("Invalid position!\n");
        return;
    }
    if (position == 1) {
        deleteAtFront(head);
        return;
    }
    struct Node* temp = *head;
    struct Node* prev = NULL;
    for (int i = 1; i < position && temp != NULL; ++i) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }
    prev->next = temp->next;
}
// void deleteAfterNodeValue(struct Node** head, int targetValue) {
//     struct Node* current = *head;

//     while (current != NULL) {
//         if (current->data == targetValue) {
//             if (current->next != NULL) {
//                 struct Node* temp = current->next;
//                 current->next = temp->next;
//                 free(temp);
//                 printf("Node deleted after the target value.\n");
//                 return;
//             }             
//             else {
//                 printf("No node to delete after. The target value is at the last node.\n");
//                 return;
//             }
//         }
//         current = current->next;
//     }
//     printf("Node with target value not found.\n");
// }
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main() {
    struct Node* head = NULL;
    int choice, data, value, position;
    struct Node* nodeToInsertAfter = NULL;
    struct Node* nodeToDeleteAfter = NULL;
    int isListCreated = 0;  // Flag to track list creation    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Create a list\n");
        printf("2. Insert at the beginning\n");
        printf("3. Insert at the end\n");
        printf("4. Insert at a particular position\n");
        printf("5. Delete from the beginning\n");
        printf("6. Delete from the end\n");
        printf("7. Delete from a particular position\n");
        printf("8. Display the list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);        
        switch (choice) {
            case 1:
                head = NULL;  // Resetting the head pointer
                isListCreated = 1;  // Marking list as created
                break;
            case 2:
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtFront(&head, data);
                break;
            case 3:
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 4:
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(&head, value, position);
                break;
            case 5:
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                deleteAtFront(&head);
                break;
            case 6:
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                deleteAtEnd(&head);
                break;
            case 7:  
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                printf("Enter position: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;
            case 8:
                if (!isListCreated) {
                    printf("List does not exist. Create a list first.\n");
                    break;
                }
                printf("\n");
                displayList(head);
                break;
            case 9:
                printf("Exiting...");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}

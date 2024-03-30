#include <stdio.h>
#include <stdlib.h>
typedef struct head {
    struct object *head;
    struct object *tail;
    int size;
} head;
typedef struct object {
    int data;
    struct object *next;
    head *prev;
} object;
head *makeSet(int data) {
    head *Header = (head *)malloc(sizeof(head));
    Header->head = (object *)malloc(sizeof(object));
    Header->tail = (object *)malloc(sizeof(object));
    Header->size = 1;
    Header->head->data = data;
    Header->head->next = NULL;
    Header->head->prev = Header;
    Header->tail = Header->head;
    return Header;
}
head *findSet(head *x) { 
    return x->head->prev; 
}
int SameSet(head *x, head *y) { 
    return (x->head->prev == y->head->prev); 
}
void Union(head *x, head *y) {
    if (x->head->prev == y->head->prev) {
        return;
    }
    head *X = x->head->prev;
    head *Y = y->head->prev;
    if (X->size > Y->size) {
        object *temp = Y->head, *prev;
        while (temp) {
            prev = temp;
            temp->prev = X;
            temp = temp->next;
        }
        X->tail->next = Y->head;
        X->tail = prev;
        X->size += Y->size;
        return;
    }
    object *temp = X->head, *prev;
    while (temp) {
        prev = temp;
        temp->prev = Y;
        temp = temp->next;
    }
    Y->tail->next = X->head;
    Y->tail = prev;
    Y->size += X->size;
}
void Connect(head *x, head *y) {
    if (!SameSet(x, y)) {
        Union(x, y);
    }
}
void printSet(head *x) {
    printf("Size of the set = %d\n", x->size);
    object *temp = x->head;
    printf("[ ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("]");
    printf("\n");
}
int main() {
    FILE *file = fopen("graph.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    int i;
    head *headers[13];
    for (i = 0; i < 13; i++) {
        headers[i] = makeSet(i + 1);
    }
    int u, v;
    while (fscanf(file, "%d %d", &u, &v) == 2) {
        Connect(headers[u - 1], headers[v - 1]);
    }
    int k = 1;
    printf("The Sets are:\n\n");
    for (i = 0; i < 13; i++) {
        if (headers[i]->head->prev == headers[i]) {
            printf("Set %d: ", k++);
            printSet(headers[i]);
            printf("root = %d\n\n", headers[i]->head->data);
        }
    }
    return 0;
}
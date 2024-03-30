#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int vertex;
    int weight;
    struct node *next;
} node;
typedef struct Graph {
    int numVertices;
    struct node **adjLists;
} Graph;
typedef struct MinHeapNode {
    int v;
    int edgeWeight;
} MinHeapNode;
typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
} MinHeap;
typedef struct Edge {
    int src, dest, weight;
} Edge;
node *createNode(int v, int weight) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (node **)malloc(vertices * sizeof(node *));
    int i;
    for (i = 0; i < vertices; i++) graph->adjLists[i] = NULL;
    return graph;
}
void addEdge(Graph *graph, int src, int dest, int weight) {
    node *newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
MinHeapNode *newMinHeapNode(int v, int key) {
    MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->edgeWeight = key;
    return minHeapNode;
}
MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    if (left < minHeap->size &&
        minHeap->array[left]->edgeWeight < minHeap->array[smallest]->edgeWeight)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->edgeWeight < minHeap->array[smallest]->edgeWeight)
        smallest = right;
    if (smallest != idx) {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
int isEmpty(MinHeap *minHeap) { return minHeap->size == 0; }
MinHeapNode *extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) return NULL;
    MinHeapNode *root = minHeap->array[0];
    MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}
void decreaseKey(MinHeap *minHeap, int v, int key) {
    int i = minHeap->pos[v];
    minHeap->array[i]->edgeWeight = key;
    while (i && minHeap->array[i]->edgeWeight <
                    minHeap->array[(i - 1) / 2]->edgeWeight) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int isInMinHeap(MinHeap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size) return 1;
    return 0;
}
void printGraph(int parent[], int n, int key[]) {
    printf("Edge Weight\n");
    int minWeight = 0;
    for (int i = 1; i < n; i++)
        printf("%c - %c %d \n", ((char)parent[i] + 65), ((char)i + 65), key[i]);
    for (int i = 1; i < n; i++) minWeight += key[i];
    printf("Minimum Weight: %d\n", minWeight);
}
void PrimMST(Graph *graph) {
    int V = graph->numVertices;
    int *parent = (int *)malloc(V * sizeof(int));
    int *key = (int *)malloc(V * sizeof(int));
    MinHeap *minHeap = createMinHeap(V);
    int v;
    for (v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
        MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        node *temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (isInMinHeap(minHeap, v) && temp->weight < key[v]) {
                key[v] = temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            temp = temp->next;
        }
    }
    printGraph(parent, V, key);
}
int main() {
    int V = 9;
    Graph *graph = createGraph(V);
    FILE *file = fopen("graphprim.txt", "r");
    int src, dest, weight;
    while (fscanf(file, "%d %d %d", &src, &dest, &weight) != EOF) {
        addEdge(graph, src, dest, weight);
    }
    fclose(file);
    PrimMST(graph);
    return 0;
}
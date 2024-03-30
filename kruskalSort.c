#include <stdio.h>
#include <stdlib.h>

// Define structures for the disjoint set data structure
typedef struct VertexSet {
    struct Vertex *head; // Pointer to the head of the linked list representing the set
    struct Vertex *tail; // Pointer to the tail of the linked list representing the set
    int size;            // Size of the set
} VertexSet;

typedef struct Vertex {
    int data;            // Data stored in the vertex (in this case, just an integer)
    struct Vertex *next; // Pointer to the next vertex in the linked list
    VertexSet *prev;     // Pointer to the parent set of the vertex
} Vertex;

// Define structure for an edge in the graph
typedef struct Edge {
    int weight, src, dest; // Weight of the edge, source vertex, and destination vertex
} Edge;

// Function to create a new set with a single vertex
VertexSet *createVertex(int data) {
    VertexSet *set = (VertexSet *)malloc(sizeof(VertexSet)); // Allocate memory for the set
    set->head = (Vertex *)malloc(sizeof(Vertex));           // Allocate memory for the head vertex
    set->tail = (Vertex *)malloc(sizeof(Vertex));           // Allocate memory for the tail vertex
    set->size = 1;                                           // Initialize size to 1
    set->head->data = data;                                  // Assign data to the head vertex
    set->head->next = NULL;                                  // Set next pointer of head to NULL
    set->head->prev = set;                                   // Set prev pointer of head to the set itself
    set->tail = set->head;                                   // Set tail to point to the head
    return set;                                              // Return the newly created set
}

// Function to merge two sets
void mergeVertices(VertexSet *x, VertexSet *y) {
    // If both sets have the same parent, do nothing
    if (x->head->prev == y->head->prev) {
        return;
    }
    VertexSet *X = x->head->prev; // Parent set of set x
    VertexSet *Y = y->head->prev; // Parent set of set y

    // Merge smaller set into larger set
    if (X->size > Y->size) {
        Vertex *temp = Y->head, *prev;
        // Traverse through all vertices of set y and update their parent to set x
        while (temp) {
            prev = temp;
            temp->prev = X;
            temp = temp->next;
        }
        // Connect the sets by updating pointers of the last vertex of set x
        X->tail->next = Y->head;
        X->tail = Y->tail; // Update tail pointer of set x
        X->size += Y->size; // Update size of set x
        return;
    } else {
        // Similar operations as above, but for set y being larger or equal
        Vertex *temp = X->head, *prev;
        while (temp) {
            prev = temp;
            temp->prev = Y;
            temp = temp->next;
        }
        Y->tail->next = X->head;
        Y->tail = X->tail;
        Y->size += X->size;
    }
}

// Function to print the Minimum Spanning Tree (MST) represented by edges
void printGraph(Edge *edge, int e) {
    int i;
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; i++) {
        printf("%c -- %c == %d\n", edge[i].src + 96, edge[i].dest + 96,
               edge[i].weight);
    }
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        totalWeight += edge[i].weight;
    }
    printf("Total weight of the MST = %d\n", totalWeight);
}

// Function to partition the edges array for quicksort
int partition(Edge *edge, int low, int high) {
    int pivot = edge[high].weight; // Choose the last element as pivot
    int i = (low - 1), j;
    // Move elements smaller than pivot to the left of pivot
    for (j = low; j <= high - 1; j++) {
        if (edge[j].weight < pivot) {
            i++;
            Edge temp = edge[i];
            edge[i] = edge[j];
            edge[j] = temp;
        }
    }
    // Swap the pivot element to its correct position
    Edge temp = edge[i + 1];
    edge[i + 1] = edge[high];
    edge[high] = temp;
    return (i + 1);
}

// Function to perform quicksort on the edges array
void sortEdges(Edge *edge, int low, int high) {
    if (low < high) {
        int pivot = partition(edge, low, high);
        sortEdges(edge, low, pivot - 1);
        sortEdges(edge, pivot + 1, high);
    }
}

// Function to find Minimum Spanning Tree using Kruskal's algorithm
void KruskalMST(VertexSet **arr, Edge *edgeArr, int e, int v) {
    int treeSize = 0; // Counter for number of edges in the MST
    Edge *result = (Edge *)malloc(v * sizeof(Edge)); // Array to store MST edges
    int j = 0;
    // Iterate through sorted edges until MST is formed or all edges are considered
    while (treeSize < e - 1 && j < e) {
        // Check if source and destination vertices of the current edge belong to different sets
        if (arr[edgeArr[j].src - 1]->head->prev !=
            arr[edgeArr[j].dest - 1]->head->prev) {
            result[treeSize] = edgeArr[j]; // Include the current edge in MST
            treeSize++; // Increment MST edge counter
            mergeVertices(arr[edgeArr[j].src - 1], arr[edgeArr[j].dest - 1]); // Merge sets of source and destination vertices
        }
        j++; // Move to the next edge
    }
    printGraph(result, v); // Print the MST
}

int main() {
    int i;
    FILE *file = fopen("graph_data.txt", "r"); // Open file containing graph data
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    int edges = 14, vertices = 9; // Define number of edges and vertices in the graph
    Edge *edgeArr = (Edge *)malloc(edges * sizeof(Edge)); // Allocate memory for edges array
    // Read edge data from file
    for (i = 0; i < edges; i++) {
        fscanf(file, "%d %d %d", &edgeArr[i].src, &edgeArr[i].dest,
               &edgeArr[i].weight);
    }
    fclose(file); // Close file
    sortEdges(edgeArr, 0, edges - 1); // Sort

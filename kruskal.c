#include <stdio.h>
#include <stdlib.h>

// Define structure for an edge
struct Edge {
    char src, dest;
    int weight;
};

// Define structure for a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// Structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// A utility function to find set of an element i
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function used for qsort()
int comp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
	int total_cost = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), comp);

    struct subset *subsets = (struct subset*) malloc(V * sizeof(struct subset));

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src - 'a');
        int y = find(subsets, next_edge.dest - 'a');

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
			total_cost = total_cost + next_edge.weight;
        }
    }

    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%c -- %c == %d\n", result[i].src, result[i].dest, result[i].weight);

	printf("Total cost of MST: %d\n", total_cost);
    free(subsets); // Free dynamically allocated memory
    return;
}

int main() {
    int V, E;
    FILE *file = fopen("graph_data.txt", "r");
    if (file == NULL) {
        printf("Could not open file graph_data.txt");
        return 1;
    }
    fscanf(file, "%d %d", &V, &E);

    struct Graph* graph = createGraph(V, E);

    for(int i=0; i<E; i++) {
        fscanf(file, " %c %c %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    fclose(file);

    KruskalMST(graph);

    free(graph->edge); // Free dynamically allocated memory
    free(graph);       // Free dynamically allocated memory

    return 0;
}

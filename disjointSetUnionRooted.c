#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 13
typedef struct
{
    int parent;
    int rank;
} Set;
Set sets[MAX_VERTICES];
void makeSet(int x)
{
    sets[x].parent = x;
    sets[x].rank = 0;
}
int findSet(int x)
{
    if (sets[x].parent != x)
        sets[x].parent = findSet(sets[x].parent);
    return sets[x].parent;
}
void unionSets(int x, int y)
{
    int rootX = findSet(x);
    int rootY = findSet(y);
    if (rootX != rootY)
    {
        if (sets[rootX].rank < sets[rootY].rank)
            sets[rootX].parent = rootY;
        else if (sets[rootX].rank > sets[rootY].rank)
            sets[rootY].parent = rootX;
        else
        {
            sets[rootY].parent = rootX;
            sets[rootX].rank++;
        }
    }
}
int main()
{
    for (int i = 1; i <= MAX_VERTICES; i++)
        makeSet(i);
    FILE *fp = fopen("graph.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    int u, v;
    while (fscanf(fp, "%d %d", &u, &v) != EOF)
        unionSets(u, v);
    fclose(fp);
    printf("Connected components:\n");
    for (int i = 1; i <= MAX_VERTICES; i++)
    {
        if (sets[i].parent == i)
        {
            printf("{");
            int first = 1;
            for (int j = 1; j <= MAX_VERTICES; j++)
            {
                if (findSet(j) == i)
                {
                    if (!first)
                        printf(", ");
                    printf("%d", j);
                    first = 0;
                }
            }
            printf("}\n");
            printf("Root: %d", i);
            printf("\n");
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
int k = 0;
void generatePermutations(int arr[], int start, int end, int **result)
{
    if (start == end)
    {
        for (int i = 0; i <= end; i++)
        {
            result[k][i] = arr[i];
        }
        k++;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(&arr[start], &arr[i]);
            generatePermutations(arr, start + 1, end, result);
            swap(&arr[start], &arr[i]);
        }
    }
}
int partition(int a[], int p, int r, int countQuick[])
{
    int x = a[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (a[j] <= x)
        {
            i = i + 1;
            swap(&a[i], &a[j]);
            (*countQuick)++;
        }
    }
    swap(&a[i + 1], &a[r]);
    (*countQuick)++;
    return i + 1;
}
void quicksort(int a[], int p, int r, int countQuick[])
{
    if (p < r)
    {
        int q = partition(a, p, r, countQuick);
        quicksort(a, p, q - 1, countQuick);
        quicksort(a, q + 1, r, countQuick);
    }
}
int main()
{
    srand(time(NULL));
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    FILE *fp = fopen("QuickSortOutput.txt", "w");
    fprintf(fp, "The Array is: ");
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        fprintf(fp, "%d ", arr[i]);
    }
    int factorial =
        1;
    for (int i = 2; i <= n; i++)
    {
        factorial *= i;
    }
    int **result =
        (int **)malloc(factorial *
                       sizeof(int *));
    int *countQuick = (int *)malloc(factorial * sizeof(int));
    for (int i = 0; i < factorial; i++)
    {
        result[i] = (int *)malloc(n * sizeof(int));
        countQuick[i] = 0;
    }
    if (
        fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    generatePermutations(arr, 0, n - 1, result);
    fprintf(fp, "\n\n");
    for (int i = 0; i < factorial; i++)
    {
        fprintf(fp, "Permutation: ");
        for (int j = 0; j < n; j++)
        {
            fprintf(fp, "%d ", result[i][j]);
        }
        fprintf(fp, "\nSorted permutation: ");
        quicksort(result[i], 0, n - 1, &countQuick[i]);
        for (int j = 0; j < n; j++)
        {
            fprintf(fp, "%d ", result[i][j]);
        }
        fprintf(fp, ": %d\n", countQuick[i]);
        fprintf(fp, "\n\n");
    }
    fclose(fp);
    printf("Results stored in 'QuickSortOutput.txt'.\n");
    return 0;
}
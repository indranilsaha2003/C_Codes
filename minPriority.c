#include <stdio.h>
#include <stdlib.h>

int count = -1;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(int *arr, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left <= count && arr[left] < arr[smallest])
        smallest = left;

    if (right <= count && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, smallest);
    }
}

void heapDecreaseKey(int *arr, int i, int key)
{
    arr[i] = key;

    while (i > 0 && arr[(i - 1) / 2] > arr[i])
    {
        swap(&arr[(i - 1) / 2], &arr[i]);
        i = (i - 1) / 2;
    }
}

void insert(int *arr, int n)
{
    int data;

    if (count == (n - 1))
    {
        printf("\nThe array is Full\nCannot Insert\n");
        return;
    }

    printf("Enter Data: ");
    scanf("%d", &data);

    count = count + 1;
    heapDecreaseKey(arr, count, data);
}

void extractMin(int *arr)
{
    int i;

    if (count == -1)
    {
        printf("\nUnderflow Condition\n");
        return;
    }

    printf("Extracted : %d\n", arr[0]);
    swap(&arr[0], &arr[count]);

    count = count - 1;

    for (i = (count - 2) / 2; i >= 0; i--)
    {
        minHeapify(arr, i);
    }
}

void printArray(int arr[])
{

    if (count == -1)
    {
        printf("\nList is empty\n");
        return;
    }
    printf("\nHeap is:\n");
    for (int i = 0; i <= count; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("\n");
}
int main()
{
    int n;
    int ch, data;

    // printf("%d\n",(-1/2));
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];

    while (1)
    {
        printf("\n1. Insert\n2. Extract minimum element\n3. display\n4. Exit\n");

        printf("Enter your Choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            insert(arr, n);
            break;

        case 2:
            extractMin(arr);
            break;

        case 3:
            printArray(arr);
            break;

        case 4:
            printf("Exiting...\n");
            exit(1);
            break;
        }
    }

    return 0;
}
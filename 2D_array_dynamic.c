#include<stdio.h>
#include<stdlib.h>

int main() {
    int *arr;
    int m, n;

    printf("Enter the no. of rows: ");
    scanf("%d", &m);
    printf("Enter the no. of columns: ");
    scanf("%d", &n);

    arr = (int*)malloc(m * n * sizeof(int));

    printf("Enter the array elements:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &arr[i * n + j]);
        }
    }

    printf("The array is:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d\t", arr[i * n + j]);
        }
        printf("\n");
    }

    free(arr);

    return 0;
}

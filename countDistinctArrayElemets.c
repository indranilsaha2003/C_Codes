#include <stdio.h>

int main()
{
    int i, j, count = 0;
    int a[] = {1, 2, 2, 3, 4, 2, 2, 3, 4, 4};
    int n = 10;
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n;){
            if (a[i] == a[j]){
                for (int k = j; k < n-1; k++)
                {
                    a[k] = a[k + 1];
                }
                n--;
            }
            else{
                j++;
            }
        }
    }
    for (i = 0; i < n; i++){
        count++;
    }
    printf("%d", count);
    return 0;
}
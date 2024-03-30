#include<stdio.h>
int main()
{
    int i,j,k,r1,c1,r2,c2;

    printf("Enter the dimensions of the 1st array: ");
    scanf("%d%d", &r1, &c1);
    printf("Enter the dimensions of the 2nd array: ");
    scanf("%d%d", &r2, &c2);

    
    int arr[r1][c1];
    int brr[r2][c2];
    int resArr[r1][c2];
    
    printf("Enter the elements of the 1st array: ");
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c1;j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("Enter the elements of the 2nd array: ");
    for(i=0;i<r2;i++)
    {
        for(j=0;j<c2;j++)
        {
            scanf("%d", &brr[i][j]);
        }
    }
    printf("\n");
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c1;j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i=0;i<r2;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d ", brr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            resArr[i][j]=0;
            for(k=0;k<c1;k++)
            {
                resArr[i][j]=resArr[i][j]+arr[i][k]*brr[k][j];
            }
        }
    }

    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d ", resArr[i][j]);
        }
        printf("\n");
    }
    return 1;
}
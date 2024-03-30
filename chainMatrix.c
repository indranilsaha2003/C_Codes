#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a, b) (a > b ? a : b)

void parenPrint(int **s, int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        parenPrint(s, i, s[i][j]);
        parenPrint(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrixChain(int *dim, int n)
{
    int i, j, k, l, q;
    int **m = (int **)malloc(n * sizeof(int *));
    int **s = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
    {
        m[i] = (int *)malloc(n * sizeof(int));
        s[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }
    for (l = 2; l < n; l++)
    {
        for (i = 1; i < n - l + 1; i++)
        {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j] + dim[i - 1] * dim[k] * dim[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            printf("%d ", s[i][j]);
        }
        printf("\n");
    }

    printf("The minimum number of multiplications required is: %d\n", m[1][n - 1]);
    printf("The optimal parenthesization is: ");
    parenPrint(s, 1, n - 1);
    printf("\n");
}

int main()
{
    int n, i;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    int *dim = (int *)malloc((n + 1) * sizeof(int));
    printf("Enter the dimensions of the matrices: ");
    for (i = 0; i <= n; i++)
    {
        scanf("%d", &dim[i]);
    }

    matrixChain(dim, n + 1);

    return 0;
}
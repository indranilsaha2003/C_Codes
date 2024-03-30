#include <stdio.h>

void pattern(int n)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (i == 1)
            printf("*\n");
        else if (i == 2)
            printf(" *\n");
        else if (i == 3)
            printf("  *\n");
        else if (i == 4)
            printf(" *\n");
    }
}

int main()
{
    int j, n, x;
    printf("Enter the limit: ");
    scanf("%d", &n);
    if (n <= 4)
    {
        pattern(n);
    }
    else if (n > 4)
    {
        x = n / 4;
        for(j = 1; j<=x; j++)
        {
            pattern(n);
        }
        n = n % 4;
        pattern(n);
    }
    return 0;
}

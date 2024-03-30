#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (a > b ? a : b)

void printLCS(char *x, char *y, int n, int m, int **dp) {
    int l = dp[n][m];
    char *s = (char *)malloc((l + 1) * sizeof(char));
    s[l] = '\0';
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            s[l - 1] = x[i - 1];
            l--;
            i--;
            j--;
        } 
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } 
        else {
            j--;
        }
    }
    printf("The longest common subsequence is: %s\n", s);
    free(s);
}

void lcsDP(char *x, char *y, int n, int m) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((m + 1) * sizeof(int));
    }
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[i - 1] == y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } 
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    printf("The length of the longest common subsequence is: %d\n", dp[n][m]);
    printLCS(x, y, n, m, dp);
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

int main() {
    int n, m;
    char *x, *y;
    printf("Enter the length of the first string: ");
    scanf("%d", &n);
    x = (char *)malloc((n + 1) * sizeof(char));
    printf("Enter the first string: ");
    scanf("%s", x);
    printf("Enter the length of the second string: ");
    scanf("%d", &m);
    y = (char *)malloc((m + 1) * sizeof(char));
    printf("Enter the second string: ");
    scanf("%s", y);
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((m + 1) * sizeof(int));
        for (int j = 0; j <= m; j++) {
            dp[i][j] = -1;
        }
    }
    lcsDP(x, y, n, m);
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
}
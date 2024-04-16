#include <stdio.h>

void spiralPrint(int m, int n, int a[100][100]) {
    int i, k = 0, l = 0;

    while (k < m && l < n) {
        for (i = l; i < n; ++i) {
            printf("%d ", a[k][i]);
        }
        k++;

        for (i = k; i < m; ++i) {
            printf("%d ", a[i][n - 1]);
        }
        n--;

        if (k < m) {
            for (i = n - 1; i >= l; --i) {
                printf("%d ", a[m - 1][i]);
            }
            m--;
        }

        if (l < n) {
            for (i = m - 1; i >= k; --i) {
                printf("%d ", a[i][l]);
            }
            l++;
        }
    }
}

int main() {
    int n;
    printf("Enter matrix size: ");
    scanf_s("%d", &n);

    int a[100][100];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf_s("%d", &a[i][j]);
        }
    }

    spiralPrint(n, n, a);
    return 0;
}
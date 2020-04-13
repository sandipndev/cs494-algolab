#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "headers/Matrix.h"

void print_optimal_parens(Matrix s, int i, int j)
{
    if (i == j)
    {
        printf("A%d", i + 1);
        return;
    }
    printf("(");
    print_optimal_parens(s, i, s.base[i][j]);
    print_optimal_parens(s, s.base[i][j] + 1, j);
    printf(")");
}

int main()
{
    int n;
    printf("? Number of matrices: ");
    scanf("%d", &n);

    int *p = calloc(n + 1, sizeof(int));
    int i, len, j, k, cost;

    for (i = 0; i < n + 1; i++)
    {
        printf("? p[%d]: ", i);
        scanf("%d", &p[i]);
    }

    Matrix m = create_matrix(n, n);
    Matrix s = create_matrix(n, n);

    for (i = 0; i < n; i++)
        m.base[i][i] = 0;

    for (len = 2; len <= n; len++)
    {
        for (i = 0; i < n - len + 1; i++)
        {
            j = i + len - 1;
            m.base[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                cost = m.base[i][k] + m.base[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (cost < m.base[i][j])
                {
                    m.base[i][j] = cost;
                    s.base[i][j] = k;
                }
            }
        }
    }

    printf("M :> \n");
    print_matrix(m);
    printf("\n");
    printf("S :> \n");
    print_matrix(s);
    printf("\nOptimal Parenthesization :>\n");
    print_optimal_parens(s, 0, n - 1);

    return 0;
}
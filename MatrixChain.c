#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "headers/Matrix.h"

void print_optimal_parens(Matrix s, int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    print_optimal_parens(s, i, s.base[i][j]);
    print_optimal_parens(s, s.base[i][j] + 1, j);
    printf(")");
}

int main()
{
    int p[7] = {5, 10, 3, 12, 5, 50, 6};

    Matrix m = create_matrix(7, 7);
    Matrix s = create_matrix(7, 7);
    int n = m.rows - 1;

    int i, len, j, k, cost;
    for (len = 2; len <= n; len++)
    {
        for (i = 1; i <= n - len + 1; i++)
        {
            j = i + len - 1;
            m.base[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                cost = m.base[i][k] + m.base[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m.base[i][j])
                {
                    m.base[i][j] = cost;
                    s.base[i][j] = k;
                }
            }
        }
    }

    print_matrix(m);
    print_matrix(s);

    print_optimal_parens(s, 1, n);

    return 0;
}
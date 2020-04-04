#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *base;
    int len;
} Set;

Set create_set(int max)
{
    Set tx;
    tx.base = (int *)calloc(max, sizeof(int));
    tx.len = max;
    return tx;
}

void make_set(Set rx, int p)
{
    if (0 <= p < rx.len)
        rx.base[p] = -1;
}

int simple_find(Set rx, int i)
{
    if (rx.base[i] == -1)
        return i;
    else
        return simple_find(rx, rx.base[i]);
}

void simple_union(Set rx, int i, int j)
{
    int i_rep = simple_find(rx, i);
    int j_rep = simple_find(rx, j);
    rx.base[i_rep] = j_rep;
}

void print_set(Set rx)
{
    printf("[ ");
    for (int i = 0; i < rx.len; i++)
        printf(" %d,", rx.base[i]);
    printf("\b]\n");
}
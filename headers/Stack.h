#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *base;
    int TOP;
    int MAX;
} Stack;

Stack create_stack(int max)
{
    Stack tx;
    tx.base = (int *)calloc(max, sizeof(int));
    tx.TOP = -1;
    tx.MAX = max;
    return tx;
}

int is_stack_empty(Stack rx)
{
    return rx.TOP == -1;
}

int is_stack_full(Stack rx)
{
    return rx.TOP == rx.MAX - 1;
}

void push(Stack *rx, int key)
{
    if (is_stack_full(*rx))
    {
        printf("[!] Stack Overflow\n");
        return;
    }
    rx->base[++rx->TOP] = key;
}

int pop(Stack *rx)
{
    if (is_stack_empty(*rx))
    {
        printf("[!] Stack Underflow\n");
        return INT_MIN;
    }
    return rx->base[rx->TOP--];
}

int peek(Stack rx)
{
    if (is_stack_empty(rx))
    {
        printf("Nothing to peek\n");
        return INT_MIN;
    }
    return rx.base[rx.TOP];
}

void print_stack(Stack rx)
{
    printf("[");
    int i;
    for (i = 0; i <= rx.TOP; i++)
    {
        printf("%d,", rx.base[i]);
    }
    if (i != 0)
        printf("\b]\n");
    else
        printf("]\n");
}

void free_stack(Stack rx)
{
    free(rx.base);
}
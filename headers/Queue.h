#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *base;
    int FRONT;
    int REAR;
    int MAX;
} Queue;

Queue create_queue(int max)
{
    Queue tx;
    tx.base = (int *)calloc(max, sizeof(int));
    tx.FRONT = -1;
    tx.REAR = -1;
    tx.MAX = max;
    return tx;
}

int is_queue_empty(Queue rx)
{
    return rx.FRONT == -1 && rx.REAR == -1;
}

int is_queue_full(Queue rx)
{
    return (rx.REAR + 1) % rx.MAX == rx.FRONT;
}

void enqueue(Queue *rx, int key)
{
    if (is_queue_full(*rx))
    {
        printf("[!] Queue Overflow!\n");
        return;
    }
    if (is_queue_empty(*rx))
    {
        rx->FRONT = 0;
        rx->REAR = 0;
    }
    else
    {
        rx->REAR = (rx->REAR + 1) % rx->MAX;
    }
    rx->base[rx->REAR] = key;
}

int dequeue(Queue *rx)
{
    if (is_queue_empty(*rx))
    {
        return INT_MIN;
    }
    if (rx->FRONT == rx->REAR)
    {
        int term = rx->base[rx->FRONT];
        rx->FRONT = -1;
        rx->REAR = -1;
        return term;
    }
    else
    {
        int term = rx->base[rx->FRONT];
        rx->FRONT = (rx->FRONT + 1) % rx->MAX;
        return term;
    }
}

void print_queue(Queue rx)
{
    printf("FRONT=%d, REAR=%d\n", rx.FRONT, rx.REAR);

    if (is_queue_empty(rx))
    {
        printf("[]\n");
        return;
    }

    printf("[ ");
    int i;
    for (i = rx.FRONT; i != rx.REAR; i = (i + 1) % rx.MAX)
        printf("%d,", rx.base[i]);
    if (rx.REAR != -1)
        printf("%d,", rx.base[rx.REAR]);
    printf("\b]\n");
}

void free_queue(Queue rx)
{
    free(rx.base);
}
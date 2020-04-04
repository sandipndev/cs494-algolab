#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void **base;
    int heap_size;
    int capacity;
} MinHeap;

MinHeap create_heap(int max)
{
    MinHeap hp;
    hp.base = (void **)calloc(max, sizeof(void *));
    hp.heap_size = -1;
    hp.capacity = max;
    return hp;
}

int is_heap_empty(MinHeap hp)
{
    return hp.heap_size == -1;
}

void insert_heap(MinHeap *hp, void *payload, int elem_size)
{
    if (hp->heap_size + 1 == hp->capacity)
    {
        printf("[HEAP_ERR] Heap Size Reached\n");
        return;
    }

    void *psv = calloc(1, elem_size);
    memcpy(psv, payload, elem_size);
    hp->base[++hp->heap_size] = psv;
}

void *extractMin(MinHeap *hp)
{
    if (hp->heap_size == -1)
    {
        printf("[HEAP_ERR] Heap Underflow\n");
        return NULL;
    }

    void *payload = hp->base[0];
    hp->base[0] = hp->base[hp->heap_size--];
    return payload;
}

void print_heap(MinHeap hp, void (*printer)(void *))
{
    printf("[HEAP, Capacity = %d, HeapTop = %d]\nElements: [ ", hp.capacity, hp.heap_size);
    for (int i = 0; i <= hp.heap_size; i++)
    {
        printer(hp.base[i]);
        printf(" ,");
    }
    printf("\b]\n");
}

void minHeapify(MinHeap *hp, int root, int (*key)(void *))
{
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    int smallest = root;

    if (l <= hp->heap_size && (*key)(hp->base[l]) < (*key)(hp->base[smallest]))
        smallest = l;
    if (r <= hp->heap_size && (*key)(hp->base[r]) < (*key)(hp->base[smallest]))
        smallest = r;

    if (smallest != root)
    {
        void *temp = hp->base[smallest];
        hp->base[smallest] = hp->base[root];
        hp->base[root] = temp;

        minHeapify(hp, smallest, key);
    }
}

void adjustHeap(MinHeap *hp, int (*key)(void *))
{
    for (int i = (hp->heap_size - 1) / 2; i >= 0; i--)
        minHeapify(hp, i, key);
}
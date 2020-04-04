#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "headers/Graph.h"
#include "headers/MinHeap.h"

struct Vertex
{
    int *distance; // Pointer to distances array
    int vtxIndex;
};

void vx_printer(void *payload)
{
    struct Vertex *vx = (struct Vertex *)payload;
    printf("{dist: %d, vIndex: %d}", *vx->distance, vx->vtxIndex);
}

int get_distance_val(void *payload)
{
    struct Vertex *vx = (struct Vertex *)payload;
    return *(vx->distance);
}

void Prim_MST(WeightedAdjacencyList graph)
{
    int *predecessors = (int *)calloc(graph.len, sizeof(int));
    int *distances = (int *)calloc(graph.len, sizeof(int));
    int *visited = (int *)calloc(graph.len, sizeof(int));

    MinHeap hp = create_heap(graph.len);
    int i;
    for (i = 0; i < graph.len; i++)
    {
        distances[i] = INT_MAX;
        predecessors[i] = -1;
        visited[i] = 0;

        struct Vertex vx = {&distances[i], i};
        insert_heap(&hp, &vx, sizeof(struct Vertex));
    }

    distances[0] = 0;
    while (!is_heap_empty(hp))
    {
        struct Vertex *vx = (struct Vertex *)extractMin(&hp);
        node *vtxEdgs = graph.base[vx->vtxIndex];

        while (vtxEdgs != NULL)
        {
            WeightedEdge *edg = (WeightedEdge *)vtxEdgs->data;
            if (!visited[edg->toVertex] && distances[edg->toVertex] > edg->weight)
            {
                distances[edg->toVertex] = edg->weight;
                predecessors[edg->toVertex] = vx->vtxIndex;
            }
            vtxEdgs = vtxEdgs->link;
        }

        visited[vx->vtxIndex] = 1;
        adjustHeap(&hp, get_distance_val);
    }

    for (i = 0; i < graph.len; i++)
        printf("%d, ", predecessors[i]);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("File not found.\n");
        exit(1);
    }

    WeightedAdjacencyList graph = weighted_adjacency_list_from_file(fp);
    Prim_MST(graph);

    fclose(fp);
}
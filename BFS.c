#include <stdio.h>
#include <stdlib.h>

#include "./headers/Graph.h"
#include "./headers/Queue.h"

void BFS(AdjacencyList, int);

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

    AdjacencyList graph = adjacency_list_from_file(fp);

    int startVertex;
    printf("? Start Vertex: ");
    scanf("%d", &startVertex);

    BFS(graph, startVertex);

    fclose(fp);
    return 0;
}

void BFS(AdjacencyList graph, int startVertex)
{
    int *visited = (int *)calloc(graph.len, sizeof(int));

    Queue q = create_queue(graph.len);
    enqueue(&q, startVertex);
    visited[startVertex] = 1;

    printf("---BFS START---\n");

    while (!is_queue_empty(q))
    {
        int v = dequeue(&q);
        printf("%d\n", v);

        node *ws = graph.base[v];
        while (ws != NULL)
        {
            Edge *w = ws->data;
            if (!visited[*w])
            {
                enqueue(&q, *w);
                visited[*w] = 1;
            }

            ws = ws->link;
        }
    }

    printf("---BFS END---\n");
}
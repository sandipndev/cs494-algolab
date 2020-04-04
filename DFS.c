#include <stdio.h>
#include <stdlib.h>

#include "./headers/Graph.h"
#include "./headers/Stack.h"

void DFS(AdjacencyList, int);

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

    DFS(graph, startVertex);

    fclose(fp);
    return 0;
}

void DFS(AdjacencyList graph, int startVertex)
{
    int *visited = (int *)calloc(graph.len, sizeof(int));

    Stack s = create_stack(graph.len);
    push(&s, startVertex);
    visited[startVertex] = 1;

    printf("---DFS START---\n");

    while (!is_stack_empty(s))
    {
        int v = pop(&s);
        printf("%d\n", v);

        node *ws = graph.base[v];
        while (ws != NULL)
        {
            Edge *w = ws->data;
            if (!visited[*w])
            {
                push(&s, *w);
                visited[*w] = 1;
            }

            ws = ws->link;
        }
    }

    printf("---DFS END---\n");
}
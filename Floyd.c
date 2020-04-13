#include <stdio.h>
#include <stdlib.h>

#include "./headers/Graph.h"

#define NIL -1

void FloydWarshall(Matrix);

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

    Matrix graph = weighted_adjacency_matrix_from_file_with_no_edge_as_int_max(fp);
    FloydWarshall(graph);

    return 0;
}

void FloydWarshall(Matrix graph)
{
    Matrix dist = create_matrix(graph.rows, graph.rows);
    Matrix pred = create_matrix(graph.rows, graph.rows);

    int i, j, k, n = graph.rows;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            dist.base[i][j] = graph.base[i][j];
            if (graph.base[i][j] == 0 || graph.base[i][j] == INF)
                pred.base[i][j] = NIL;
            else
                pred.base[i][j] = i;
        }
    }

    printf("-------------- D0 --------------\n");
    printf("DIST:\n");
    print_matrix(dist);
    printf("PRED:\n");
    print_matrix(pred);
    printf("\n");

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist.base[i][j] > dist.base[i][k] + dist.base[k][j])
                {
                    dist.base[i][j] = dist.base[i][k] + dist.base[k][j];
                    pred.base[i][j] = pred.base[i][k];
                }
            }
        }

        printf("\n\n-------------- D%d --------------\n", k);
        printf("DIST:\n");
        print_matrix(dist);
        printf("PRED:\n");
        print_matrix(pred);
        printf("\n");
    }
}
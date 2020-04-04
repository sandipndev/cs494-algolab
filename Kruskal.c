#include <stdio.h>
#include <stdlib.h>

#include "./headers/Graph.h"
#include "./headers/Set.h"

struct graph_edge
{
    int u;
    int v;
    int weight;
};

int get_weight(void *rx)
{
    struct graph_edge *gedg = rx;
    return gedg->weight;
}

void printer_GraphEdge(void *rx)
{
    struct graph_edge *gedg = rx;
    printf("{%d, %d, %d}", gedg->u, gedg->v, gedg->weight);
}

void Kruskal_Minimal_Spanning_Tree(WeightedAdjacencyMatrix graph)
{
    Set s = create_set(graph.rows);

    for (int i = 0; i < graph.rows; i++)
        make_set(s, i);

    /* Sort by weights */
    struct graph_edge gedg;
    node *weights_list = NULL;

    int i, j;
    for (i = 0; i < graph.rows; i++)
    {
        for (j = 0; j < graph.cols; j++)
        {
            if (j >= i && graph.base[i][j] != 0)
            {
                // Has an edge
                gedg.u = i;
                gedg.v = j;
                gedg.weight = graph.base[i][j];

                weights_list = insert_elem_sorted(weights_list, &gedg, sizeof(struct graph_edge), get_weight);
            }
        }
    }

    printf("---BEGIN SPANNING TREE---\n");

    /* For every u,v in sorted */
    while (weights_list != NULL)
    {
        void *data = weights_list->data;
        struct graph_edge *edg = data;

        if (simple_find(s, edg->u) != simple_find(s, edg->v))
        {
            printf("%d <-> %d\n", edg->u, edg->v);
            simple_union(s, edg->u, edg->v);
        }

        weights_list = weights_list->link;
    }

    printf("---END SPANNING TREE---\n");
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

    WeightedAdjacencyMatrix graph = weighted_adjacency_matrix_from_file(fp);
    Kruskal_Minimal_Spanning_Tree(graph);

    fclose(fp);
    return 0;
}

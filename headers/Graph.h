#define LIMIT 100
#define INF 9999

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Matrix.h"
#include "./List.h"

typedef int Edge;

typedef struct
{
    int weight;
    int toVertex;
} WeightedEdge;

/* Will Consist of Edge */
typedef struct
{
    node **base;
    int len;
} AdjacencyList;

/* Will Consist of WeightedEdge */
typedef struct
{
    node **base;
    int len;
} WeightedAdjacencyList;

typedef Matrix WeightedAdjacencyMatrix;

Matrix adjacency_matrix_from_file(FILE *fp)
{
    char line[LIMIT];
    fgets(line, LIMIT, fp);
    int len = atoi(line);

    Matrix tx = create_matrix(len, len);

    int i = 0, j;
    while (fgets(line, LIMIT, fp) != NULL)
    {
        char ch = line[0];
        j = 0;
        while (ch != '\0')
        {
            if (ch == '0')
                tx.base[i][j / 2] = 0;
            else if (ch == '1')
                tx.base[i][j / 2] = 1;
            ch = line[++j];
        }
        i++;
    }

    return tx;
}

WeightedAdjacencyMatrix weighted_adjacency_matrix_from_file(FILE *fp)
{
    char line[LIMIT];

    fgets(line, LIMIT, fp);
    int len = atoi(line);

    WeightedAdjacencyMatrix tx = create_matrix(len, len);
    tx.rows = len;
    tx.cols = len;

    int i = 0, j;
    while (fgets(line, LIMIT, fp) != NULL)
    {
        char *weight = strtok(line, " ");
        j = 0;
        while (weight != NULL)
        {
            tx.base[i][j++] = atoi(weight);
            weight = strtok(NULL, " ");
        }
        i++;
    }

    return tx;
}

WeightedAdjacencyMatrix weighted_adjacency_matrix_from_file_with_no_edge_as_int_max(FILE *fp)
{
    char line[LIMIT];

    fgets(line, LIMIT, fp);
    int len = atoi(line);

    WeightedAdjacencyMatrix tx = create_matrix(len, len);
    tx.rows = len;
    tx.cols = len;

    int i = 0, j;
    while (fgets(line, LIMIT, fp) != NULL)
    {
        char *weight = strtok(line, " ");
        j = 0;
        while (weight != NULL)
        {
            int r = atoi(weight);
            tx.base[i][j++] = r != 0 ? r : (i != j ? INF : 0);
            weight = strtok(NULL, " ");
        }
        i++;
    }

    return tx;
}

AdjacencyList adjacency_list_from_file(FILE *fp)
{
    AdjacencyList list;
    Edge edg;

    char line[LIMIT];
    fgets(line, LIMIT, fp);
    int len = atoi(line);

    list.base = (node **)calloc(len, sizeof(node *));
    list.len = len;

    int i, j;
    for (i = 0; i < len; i++)
        list.base[i] = NULL;

    i = 0;
    while (fgets(line, LIMIT, fp) != NULL)
    {
        char ch = line[0];
        j = 0;
        while (ch != '\0')
        {
            if (ch == '1')
            {
                edg = j / 2;
                list.base[i] = insert_last(list.base[i], &edg, sizeof(Edge));
            }
            ch = line[++j];
        }
        i++;
    }

    return list;
}

void printer_Edge(void *rx)
{
    Edge *edg = rx;
    printf("%d", *edg);
}

void print_adjacency_list(AdjacencyList list)
{
    int i;
    for (i = 0; i < list.len; i++)
    {
        printf("(%d) -> ", i);
        display_list(list.base[i], printer_Edge);
    }
}

WeightedAdjacencyList weighted_adjacency_list_from_file(FILE *fp)
{
    WeightedAdjacencyList list;
    WeightedEdge edg;

    char line[LIMIT];
    fgets(line, LIMIT, fp);
    int len = atoi(line);

    list.base = (node **)calloc(len, sizeof(node *));
    list.len = len;

    int i, j;
    for (i = 0; i < len; i++)
        list.base[i] = NULL;

    i = 0;
    while (fgets(line, LIMIT, fp) != NULL)
    {
        char *weight = strtok(line, " ");
        j = 0;
        while (weight != NULL)
        {
            edg.toVertex = j++;
            edg.weight = atoi(weight);

            if (edg.weight != 0)
                list.base[i] = insert_last(list.base[i], &edg, sizeof(WeightedEdge));

            weight = strtok(NULL, " ");
        }
        i++;
    }

    return list;
}

void printer_WeightedEdge(void *rx)
{
    WeightedEdge *edg = rx;
    printf("{to-> (%d), wt-> (%d)}", edg->toVertex, edg->weight);
}

void print_weighted_adjacency_list(WeightedAdjacencyList list)
{
    int i;
    for (i = 0; i < list.len; i++)
    {
        printf("(%d) -> ", i);
        display_list(list.base[i], printer_WeightedEdge);
    }
}
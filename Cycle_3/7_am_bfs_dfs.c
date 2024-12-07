/* Program: BFS and DFS using AM
 * Date: 7 Dec. '24
 *
 * Implement breadth-first search and depth-first search
 * for an undirected graph using an adjacency matrix.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* An adjacency matrix is always n-by-n. */
typedef struct {
    size_t n;  /* for rows and columns. */
    bool** am; /* for the adjacency matrix. */
} AM;
/* Allocate using calloc.  This will set all edges to false initially. */

void add_edge(AM* a, int u, int v)
/* Add an edge between v and u. */
{
    a->am[u][v] = true;
    a->am[v][u] = true;
}

void read_adjacency_matrix(AM* a)
/* Read an adjacency matrix representation
 * for an undirected graph. */
{
    printf("Number of vertices: ");
    scanf("%zu", &a->n);

    /* Firstly, allocate an array of pointers.  For each pointer in this array,
     * allocate an array of concern of the required size. */
    a->am = calloc(a->n, sizeof(bool*)); 
    for (size_t i = 0; i < a->n; ++i)
        a->am[i] = calloc(a->n, sizeof (bool));

    size_t edges;
    printf("Number of edges: "); scanf("%zu", &edges);

    /* (u v) represents an edge. */
    size_t u, v;
    printf("Enter edges (u v):\n");
    for (size_t i = 0; i < edges; i++) {
        scanf("%zu %zu", &u, &v);
        add_edge(a, u, v);
    }
}

void bfs(AM a, size_t z)
/* Do a BFS from vertex z. 
 * This procedure is iterative. */
{
    size_t queue[a.n];
    size_t r = 0, f = 0;
    bool explored[a.n];
    /* Since this is an undirected graph, we need to check whether a vertex was
     * explored to avoid tracing back that creats unending traversal. */

    queue[r++] = z;
    explored[z] = true;

    printf("BFS: ");
    while (f < r) {
        size_t x = queue[f++];
        printf("%zu ", x);
        for (size_t i = 0; i < a.n; i++) {
            if (a.am[x][i] && !explored[i]) {
                queue[r++] = i;
                explored[i] = true;
            }
        }
    }
    puts("");
}

void dfs(AM a, size_t z)
/* Do a DFS from vertex z. 
 * This procedure is iterative. */
{
    size_t stack[a.n];
    size_t t = 0;
    bool explored[a.n];

    stack[t++] = z;
    explored[z] = true;

    printf("DFS: ");
    while (t > 0) {
        size_t x = stack[--t];
        printf("%zu ", x);
        for (size_t i = 0; i < a.n; i++) {
            if (a.am[x][i] && !explored[i]) {
                stack[t++] = i;
                explored[i] = true;
            }
        }
    }
    puts("");
}

int main(int argc, char** argv)
{
    /* Declare and initialize an adjacency matrix. */
    AM a;
    read_adjacency_matrix(&a);

    /* Determine the starting vertex for BFS and DFS. */
    size_t z;
    printf("\nStarting vertex: ");
    scanf("%zu", &z);

    bfs(a, z);
    dfs(a, z);

    /* Free heap memory. */
    for(size_t i = 0; i < a.n; ++i)
        free(a.am[i]);
    free(a.am);

    return 0;
}

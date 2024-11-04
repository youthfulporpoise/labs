/* Program: DFS & BFS WITH AL
 *
 * Implement depth-first search and breadth-first search
 * on an undirected graph represented as an adjacency list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node Node;
typedef struct node {
    int data;
    Node* next;
} Node;
typedef Node* LinkedList;

/* Adjecency list */
LinkedList* al;

LinkedList add_edge(LinkedList ll, int v)
/* Add v to end of the linked list. */
{
    Node* x = malloc(sizeof (Node));
    x->data = v;
    if (ll == NULL) ll = x;
    else {
        Node* p = ll;
        ll = x; x->next = p;
    }
    return ll;
}

size_t read_adjacency_list()
/* Read an adjacency list representation of
 * an undirected graph. */
{
    size_t vertices; /* is the number of vertices. */
    printf("Number of vertices: "); scanf("%zu", &vertices);
    al = malloc(vertices * sizeof (LinkedList)); 

    int u, v; /* (u v) is an edge. */
    size_t edges;
    printf("Number of edges: "); scanf("%zu", &edges);
    printf("Enter edges (u v):\n");
    for (size_t i = 0; i < edges; ++i) {
       scanf("%d %d", &u, &v);
        if (u >= vertices || v >= vertices) {
            printf("%d, %d: invalid vertices\n", u, v);
            return vertices;
        }
        al[u] = add_edge(al[u], v);
        al[v] = add_edge(al[v], u);
        /* This is an undirected graph. */
    }
    return vertices;
}

void bfs(int vertex, size_t vertices)
/* Do a BFS from the vertex.  This implementation
 * is iterative. */
{
    bool explored[vertices];
    int queue[vertices]; size_t r = 0, f = 0;

    printf("BFS: ");
    queue[r++] = vertex; explored[vertex] = true;
    while (f < r) {
        int x = queue[f++];
        printf("%d ", x);
        Node* p = al[x];
        while (p != NULL) {
            if (!explored[p->data]) {
                queue[r++] = p->data;
                explored[p->data] = true;
            } p = p->next;
        }
    }
    puts("");
}

void dfs(int vertex, size_t vertices)
/* Do a DFS from the vertex. This implementation
 * is iterative. */
{
    bool explored[vertices];
    int stack[vertices]; size_t t = 0;

    printf("DFS: ");
    Node* p = al[vertex];
    stack[t++] = vertex; explored[vertex] = true;
    while (t > 0) {
        int x = stack[--t];
        printf("%d ", x);
        Node* p = al[x];
        while (p != NULL) {
            if (!explored[p->data]) {
                stack[t++] = p->data;
                explored[p->data] = true;
            } p = p->next;
        }
    }
    puts("");
}

int main()
{
    size_t vertices = read_adjacency_list();
    int vertex;
    printf("\nStarting vertex: "); scanf("\n%d", &vertex);
    bfs(vertex, vertices);
    dfs(vertex, vertices);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define       MAXVERT       64
#define       INF           999


/* The graph struct contains the cost between the nodes and the numbers of nodes. We will
 * represent infinity (INF) as 9999. The valid distance and cost values are 0, 1, 2, ...
 * The number of nodes are (n <= MAXVERT).
 */

struct graph {
  int cost[MAXVERT][MAXVERT];
  size_t n;
} g;


/* This is multi-purpose buffer used for passing string inputs and outputs between
 * procedures. It avoids the pain points associated with creating bespoke strings or even
 * dynamic ones.
 */

char buffer[512];


void construct_graph(void)
{
  printf("Enter the adjacency matrix (%zu):\n", g.n);
  for (size_t i = 0; i < g.n; ++i) {
    for (size_t j = 0; j < g.n; ++j) {
      scanf("%d", &g.cost[i][j]);

      /* The diagonal elements of the adjacency matrix are always zero because moving from
       * A to A must not have any cost. So we do the following check and assign.
       */

      if (i == j)
        g.cost[i][j] = 0;
    }
  }
}


/* This is a procedure to print the shortest path when displaying the routing table inside
 * the following Dijkstra’s algorithm procedure.
 */

void print_path(size_t v, int *parent)
{
  char tmp[64];
  sprintf(buffer, "%zu", v);
  v = parent[v];

  while (v != -1) {
    sprintf(tmp, " <- %zu", v);
    strcat(buffer, tmp);
    v = parent[v];
  }
}


/* Dijkstra’s algorithm finds the shortest path from the given source node to every other
 * node. Although it can be used to find the shortest path between two specific nodes, by
 * terminating the procedure after determining the shortest path between those two nodes.
 */

void dijkstra(size_t src)
{
  int was_visited[g.n],   /* nodes visted globally; shortest path found */
      parent[g.n],        /* to calculate the path, not just distance */
      src_dist[g.n],      /* distances w/r/t to src */
      nearest,                /* shortest-path node chosen */
      min_dist;               /* temp var for min dist found */

  for (size_t i = 0; i < g.n; ++i) {
    src_dist[i] = g.cost[src][i];
    was_visited[i] = false;
    parent[i] = -1;
  }

  src_dist[src] = 0;
  was_visited[src] = true;

  for (size_t count = 0; count < g.n - 1; ++count) {
    min_dist = INF;
    nearest = -1;

    /* The actual algorithm uses a priority queue to find the nearest node, however we use
     * simple linear iteration.
     */

    for (size_t i = 0; i < g.n; ++i) {
      if (!was_visited[i] && src_dist[i] < min_dist) {
        min_dist = src_dist[i];
        nearest = i;
      }
    }

    /* If there are no more reachable neighbours, we break.
     */

    if (nearest == -1)
      break;

    was_visited[nearest] = true;

    /* This handles an edge case where the parent of the first nearest node of the source
     * node will not be updated to the source node.
     */

    if (parent[nearest] == -1)
      parent[nearest] = src;

    /* We compare the cost of (src -> v) and (src -> nearest -> v), and if the latter is
     * lower than the former, we set the shortest distance as the latter. This is the
     * relaxation step of the algorithm.
     */

    for (size_t v = 0; v < g.n; ++v) {
      if (!was_visited[v] && g.cost[nearest][v] != INF)
        if (src_dist[v] > src_dist[nearest] + g.cost[nearest][v]) {
          src_dist[v] = src_dist[nearest] + g.cost[nearest][v];
          parent[v] = nearest;
        }
    }
  }

  /* Finally, print the routing table for the give soure node.
   */

  printf("\nRouting Table of Node %zu\n", src);
  printf("------ ------ ------\n");
  printf("%-6s %-6s %-6s\n", "DST", "COST", "PRNT");
  printf("------ ------ ------\n");
  for (size_t i = 0; i < g.n; ++i) {
    if (src_dist[i] == INF)
      printf("%-6zu %-6s %-6s\n", i, "INF", "n/a");
    else {
      print_path(i, parent);
      printf("%-6zu %-6d %-6s\n", i, src_dist[i], buffer);
    }
  }
  printf("------ ------ ------\n");
}


int main(int argc, char **argv)
{
  size_t src;

  printf("Number of nodes (%d max.): ", MAXVERT);
  scanf("%zu", &g.n);
  if (MAXVERT < g.n || g.n <= 0) {
    puts("Invalid");
    return 1;
  }
  construct_graph();

  for (size_t i = 0; i < g.n; ++i)
    dijkstra(i);

  return 0;
}

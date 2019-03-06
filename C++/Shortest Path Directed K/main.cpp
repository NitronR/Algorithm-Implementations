#include <iostream>
#include <limits.h>
using namespace std;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

class Graph
{
  public:
    int V, **graph;
    Graph(int v)
    {
        V = v;
        graph = new int *[V];
        for (int i = 0; i < V; i++)
            graph[i] = new int[V];
    }

    int shortestKPath(int u, int v, int k)
    {
        if (k == 0 && u == v)
            return 0;
        if (k == 1 && graph[u][v] != INT_MAX)
            return graph[u][v];
        if (k <= 0)
            return INT_MAX;

        int res = INT_MAX;

        for (int i = 0; i < V; i++)
        {
            if (graph[u][v] != INT_MAX && u != i && v != i)
            {
                int rec_res = shortestKPath(i, v, k - 1);
                if (rec_res != INT_MAX)
                    res = min(res, rec_res + graph[u][i]);
            }
        }

        return res;
    }
};

int main()
{
    Graph g(4);

    g.graph[0][0] = 0;
    g.graph[0][1] = 10;
    g.graph[0][2] = 3;
    g.graph[0][3] = 2;

    g.graph[1][0] = INT_MAX;
    g.graph[1][1] = 0;
    g.graph[1][2] = INT_MAX;
    g.graph[1][3] = 7;

    g.graph[2][0] = INT_MAX;
    g.graph[2][1] = INT_MAX;
    g.graph[2][2] = 0;
    g.graph[2][3] = 6;

    g.graph[3][0] = INT_MAX;
    g.graph[3][1] = INT_MAX;
    g.graph[3][2] = INT_MAX;
    g.graph[3][3] = 0;

    int u = 0, v = 3, k = 2;

    cout << "Weight of the shortest path is " << g.shortestKPath(u, v, k) << endl;

    return 0;
}
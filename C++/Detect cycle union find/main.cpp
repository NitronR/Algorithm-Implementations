#include <iostream>
using namespace std;

class Edge
{
  public:
    int src, dest;
};

class Graph
{
  public:
    int V, E;
    Edge *edges;

    Graph(int v, int e)
    {
        V = v;
        E = e;
        edges = new Edge[e];
    }
    bool isCyclic();
};

int find(int p[], int x)
{
    if (x != p[x])
    {
        p[x] = find(p, p[x]);
    }
    return p[x];
}

void Union(int p[], int x, int y)
{
    int u = find(p, x);
    int v = find(p, y);

    if (u != v)
    {
        p[v] = u;
    }
}

bool Graph::isCyclic()
{
    int *p = new int[V];

    for (int i = 0; i < V; i++)
    {
        p[i] = i;
    }

    for (int i = 0; i < E; i++)
    {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (find(p, u) == find(p, v))
        {
            return true;
        }

        Union(p, u, v);
    }
    return false;
}

int main()
{

    int V = 3, E = 3;
    Graph graph(V, E);

    // add edge 0-1
    graph.edges[0].src = 0;
    graph.edges[0].dest = 1;

    // add edge 1-2
    graph.edges[1].src = 1;
    graph.edges[1].dest = 2;

    // add edge 0-2
    graph.edges[2].src = 0;
    graph.edges[2].dest = 2;

    if (graph.isCyclic())
        cout << "graph contains cycle" << endl;
    else
        cout << "graph doesn't contain cycle" << endl;

    return 0;
}
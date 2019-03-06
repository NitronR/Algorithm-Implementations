#include <iostream>
#include <limits.h>
using namespace std;

class Edge
{
  public:
    int src, dest, weight;
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
        edges = new Edge[E];
    }
};

void printDist(int *dist, int src, int V)
{
    cout << "Source vertex: " << src << endl;
    cout << "Vertex\t"
         << "Distance from source" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << "\t" << dist[i] << endl;
    }
}

void BellmanFord(Graph graph, int src)
{
    int V = graph.V;
    int E = graph.E;
    int *dist = new int[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    for (int i = 1; i < V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph.edges[j].src;
            int v = graph.edges[j].dest;
            int weight = graph.edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = graph.edges[i].src;
        int v = graph.edges[i].dest;
        int weight = graph.edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            cout << "Contains negative weight cycle" << endl;
            return;
        }
    }

    printDist(dist, src, graph.V);
}

int main()
{
    int V = 5;
    int E = 8;
    Graph graph(V, E);

    graph.edges[0].src = 0;
    graph.edges[0].dest = 1;
    graph.edges[0].weight = -1;

    graph.edges[1].src = 0;
    graph.edges[1].dest = 2;
    graph.edges[1].weight = 4;

    graph.edges[2].src = 1;
    graph.edges[2].dest = 2;
    graph.edges[2].weight = 3;

    graph.edges[3].src = 1;
    graph.edges[3].dest = 3;
    graph.edges[3].weight = 2;

    graph.edges[4].src = 1;
    graph.edges[4].dest = 4;
    graph.edges[4].weight = 2;

    graph.edges[5].src = 3;
    graph.edges[5].dest = 2;
    graph.edges[5].weight = 5;

    graph.edges[6].src = 3;
    graph.edges[6].dest = 1;
    graph.edges[6].weight = 1;

    graph.edges[7].src = 4;
    graph.edges[7].dest = 3;
    graph.edges[7].weight = -3;

    BellmanFord(graph, 0);
    return 0;
}
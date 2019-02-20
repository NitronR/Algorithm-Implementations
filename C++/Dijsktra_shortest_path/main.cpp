#include <iostream>
#include <limits.h>
using namespace std;
#define V 9

int minDist(int dist[], bool sptSet[])
{
    int min_index, mn = INT_MAX;

    for (int i = 0; i < V; i++)
    {
        if (!sptSet[i] && dist[i] <= mn)
        {
            min_index = i;
            mn = dist[i];
        }
    }

    return min_index;
}

int *dijsktra(int graph[V][V], int s)
{
    int *dist = new int[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[s] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        int u = minDist(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    return dist;
}

int main()
{

    /* Let us create the example graph discussed above */
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    int *dist = dijsktra(graph, 0);

    cout << "Shortest distances:" << endl;

    for (int i = 0; i < V; i++)
    {
        cout << i << ":" << dist[i] << endl;
    }
    return 0;
}
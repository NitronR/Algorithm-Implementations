#include <iostream>
#include <limits.h>
using namespace std;

class Graph
{
    int **dist;

    void FloydWarshall()
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                dist[i][j] = adjMat[i][j];
            }
        }

        for (int k = 0; k < V; k++)
            for (int i = 0; i < V; i++)
                for (int j = 0; j < V; j++)
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                        if (dist[i][k] + dist[k][j] < dist[i][j])
                            dist[i][j] = dist[i][k] + dist[k][j];
    }

  public:
    int V, **adjMat;

    Graph(int v)
    {
        V = v;

        adjMat = new int *[V];
        for (int i = 0; i < V; i++)
            adjMat[i] = new int[V];

        dist = new int *[V];
        for (int i = 0; i < V; i++)
            dist[i] = new int[V];
    }

    void printDists()
    {
        FloydWarshall();

        cout << "Shorted distance matrix:" << endl;

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] == INT_MAX)
                    cout << "INF\t";
                else
                    cout << dist[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph graph(4);

    graph.adjMat[0][0] = 0;
    graph.adjMat[0][1] = 5;
    graph.adjMat[0][2] = INT_MAX;
    graph.adjMat[0][3] = 10;

    graph.adjMat[1][0] = INT_MAX;
    graph.adjMat[1][1] = 0;
    graph.adjMat[1][2] = 3;
    graph.adjMat[1][3] = INT_MAX;

    graph.adjMat[2][0] = INT_MAX;
    graph.adjMat[2][1] = INT_MAX;
    graph.adjMat[2][2] = 0;
    graph.adjMat[2][3] = 1;

    graph.adjMat[3][0] = INT_MAX;
    graph.adjMat[3][1] = INT_MAX;
    graph.adjMat[3][2] = INT_MAX;
    graph.adjMat[3][3] = 0;

    graph.printDists();
    return 0;
}
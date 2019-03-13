#include <iostream>
using namespace std;

class Graph
{
    int **graph, **reach;

    void transitiveClosure()
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                reach[i][j] = graph[i][j];
            }
        }

        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                }
            }
        }
    }

  public:
    int V;

    Graph(int V)
    {
        this->V = V;
        graph = new int *[V];

        for (int i = 0; i < V; i++)
        {
            graph[i] = new int[V];
            for (int j = 0; j < V; j++)
                graph[i][j] = 0;
        }

        reach = new int *[V];

        for (int i = 0; i < V; i++)
            reach[i] = new int[V];
    }

    void addEdge(int u, int v)
    {
        graph[u][v] = 1;
    }

    void printTransClosure()
    {
        transitiveClosure();

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << reach[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph graph(4);

    graph.addEdge(0, 0);
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(1, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 3);

    graph.printTransClosure();

    return 0;
}
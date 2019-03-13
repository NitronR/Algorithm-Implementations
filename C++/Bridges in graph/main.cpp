#include <iostream>
#include <vector>
using namespace std;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

class Graph
{
    int V, *disc, *low, *parent, time;
    vector<int> *adj;

    void bridgeUtil(int u)
    {
        disc[u] = low[u] = ++time;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (disc[v] == -1)
            {
                parent[v] = u;

                bridgeUtil(v);

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u])
                {
                    cout << u << " " << v << endl;
                }
            }
            else if (parent[u] != v)
            {
                low[u] = min(low[u], low[v]);
            }
        }
    }

  public:
    Graph(int V)
    {
        this->V = V;
        adj = new vector<int>[V];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printBridges()
    {
        disc = new int[V];
        low = new int[V];
        parent = new int[V];

        for (int i = 0; i < V; i++)
        {
            disc[i] = -1;
            low[i] = -1;
            parent[i] = -1;
        }

        time = 0;

        for (int i = 0; i < V; i++)
        {
            if (disc[i] == -1)
            {
                bridgeUtil(i);
            }
        }
    }
};

int main()
{
    cout << "\nBridges in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.printBridges();

    cout << "\nBridges in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.printBridges();

    cout << "\nBridges in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.printBridges();
    return 0;
}
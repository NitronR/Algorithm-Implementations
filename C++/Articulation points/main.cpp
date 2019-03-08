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
    bool *ap;
    vector<int> *adj;

    void APUtil(int u)
    {
        int children = 0;

        disc[u] = low[u] = ++time;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];

            if (disc[v] == -1)
            {
                children++;
                parent[v] = u;

                APUtil(v);

                low[u] = min(low[u], low[v]);

                if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]))
                {
                    ap[u] = true;
                }
            }
            else if (v != parent[u])
            {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

  public:
    Graph(int v)
    {
        V = v;
        disc = new int[V];
        low = new int[V];
        parent = new int[V];
        adj = new vector<int>[V];
        ap = new bool[V];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printAP()
    {
        // Init
        for (int i = 0; i < V; i++)
        {
            disc[i] = -1;
            low[i] = -1;
            parent[i] = -1;
            ap[i] = false;
        }
        time = 0;

        for (int i = 0; i < V; i++)
        {
            if (disc[i] == -1)
            {
                APUtil(i);
            }
        }

        for (int i = 0; i < V; i++)
            if (ap[i])
                cout << i << " ";
    }
};

int main()
{
    cout << "\nArticulation points in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.printAP();

    cout << "\nArticulation points in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.printAP();

    cout << "\nArticulation points in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.printAP();

    return 0;
}
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

    bool isBCUtil(int u)
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
                
                if(isBCUtil(v))
                    return true;

                low[u] = min(low[u], low[v]);

                if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]))
                {
                    return true;
                }
            }
            else if (v != parent[u])
            {
                low[u] = min(low[u], disc[v]);
            }
        }

        return false;
    }

  public:
    Graph(int v)
    {
        V = v;
        disc = new int[V];
        low = new int[V];
        parent = new int[V];
        adj = new vector<int>[V];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool isBC()
    {
        // Init
        for (int i = 0; i < V; i++)
        {
            disc[i] = -1;
            low[i] = -1;
            parent[i] = -1;
        }
        time = 0;

        if (isBCUtil(0))
        {
            return false;
        }

        for (int i = 0; i < V; i++)
        {
            if (disc[i] == -1)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    Graph g1(2);
    g1.addEdge(0, 1);
    g1.isBC() ? cout << "Yes\n" : cout << "No\n";

    Graph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.addEdge(2, 4);
    g2.isBC() ? cout << "Yes\n" : cout << "No\n";

    Graph g3(3);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.isBC() ? cout << "Yes\n" : cout << "No\n";

    Graph g4(5);
    g4.addEdge(1, 0);
    g4.addEdge(0, 2);
    g4.addEdge(2, 1);
    g4.addEdge(0, 3);
    g4.addEdge(3, 4);
    g4.isBC() ? cout << "Yes\n" : cout << "No\n";

    Graph g5(3);
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(2, 0);
    g5.isBC() ? cout << "Yes\n" : cout << "No\n";

    return 0;
}
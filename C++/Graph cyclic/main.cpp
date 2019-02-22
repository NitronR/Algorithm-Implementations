#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph
{
  public:
    vector<int> *adj;
    int V;
    Graph(int v)
    {
        V = v;
        adj = new vector<int>[v];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    bool isCyclicUtil(int u, bool *visited, bool *recStack)
    {
        if (!visited[u])
        {
            visited[u] = true;
            recStack[u] = true;

            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];
                if (!visited[v] && isCyclicUtil(v, visited, recStack))
                {
                    return true;
                }
                else if (recStack[v])
                {
                    return true;
                }
            }
        }
        recStack[u] = false;
        return false;
    }

    bool isCyclic()
    {
        bool *visited = new bool[V];
        bool *recStack = new bool[V];

        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            recStack[i] = true;
        }

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && isCyclicUtil(i, visited, recStack))
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    if (g.isCyclic())
        cout << "Graph contains cycle" << endl;
    else
        cout << "Graph doesn't contain cycle" << endl;
    return 0;
}
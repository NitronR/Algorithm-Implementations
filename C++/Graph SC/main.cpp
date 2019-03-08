#include <iostream>
#include <vector>
using namespace std;

class Graph
{
    vector<int> *adj;
    bool *visited;

    void DFSUtil(int u)
    {
        visited[u] = true;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (!visited[v])
                DFSUtil(v);
        }
    }

  public:
    int V;

    Graph(int V)
    {
        this->V = V;
        adj = new vector<int>[V];
        visited = new bool[V];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    bool isSC()
    {
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }
        DFSUtil(0);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                return false;
        }

        Graph transpose = getTranspose();

        for (int i = 0; i < V; i++)
        {
            transpose.visited[i] = false;
        }

        transpose.DFSUtil(0);

        for (int i = 0; i < V; i++)
        {
            if (!transpose.visited[i])
                return false;
        }

        return true;
    }

    Graph getTranspose()
    {
        Graph transpose(V);

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                int v = adj[i][j];
                transpose.adj[v].push_back(i);
            }
        }

        return transpose;
    }
};

int main()
{
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 0);
    g1.addEdge(2, 4);
    g1.addEdge(4, 2);
    g1.isSC() ? cout << "Yes\n" : cout << "No\n";

    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.isSC() ? cout << "Yes\n" : cout << "No\n";
    return 0;
}
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

    void DFS(int s)
    {
        int u, v;
        bool *visited = new bool[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;

        stack<int> q;

        q.push(s);
        visited[s] = true;
        while (!q.empty())
        {
            u = q.top();

            cout << u << " " << endl;
            q.pop();

            for (int i = 0; i < adj[u].size(); i++)
            {
                v = adj[u][i];
                if (!visited[adj[u][i]])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
};

int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 0);
    g.addEdge(3, 3);

    cout << "Following is Depth First Traversal "
         << "(starting from vertex 2) \n";
    g.DFS(2);
    return 0;
}
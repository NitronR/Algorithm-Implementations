#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph
{
  public:
    int V;
    vector<int> *adj;

    Graph(int v)
    {
        V = v;
        adj = new vector<int>[v];
    }

    Graph getTranspose()
    {
        Graph g(V);

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                g.addEdge(adj[i][j], i);
            }
        }

        return g;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void printSCCs();
};

void DFSUtil(int u, Graph g, bool visited[])
{
    visited[u] = true;
    cout << u << " ";
    for (int i = 0; i < g.adj[u].size(); i++)
    {
        if (!visited[g.adj[u][i]])
        {
            DFSUtil(g.adj[u][i], g, visited);
        }
    }
}

void fillOrder(int u, bool visited[], stack<int> &Stack, Graph g)
{
    visited[u] = true;
    for (int i = 0; i < g.adj[u].size(); i++)
    {
        if (!visited[g.adj[u][i]])
        {
            fillOrder(g.adj[u][i], visited, Stack, g);
        }
    }

    Stack.push(u);
}

void Graph::printSCCs()
{
    stack<int> Stack;

    bool *visited = new bool[V];

    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            fillOrder(i, visited, Stack, *this);

    Graph transpose = getTranspose();

    for (int i = 0; i < V; i++)
        visited[i] = false;

    cout << "SCCS:" << endl;
    while (!Stack.empty())
    {
        int u = Stack.top();
        Stack.pop();
        if (!visited[u])
        {
            DFSUtil(u, transpose, visited);
            cout << endl;
        }
    }
}

int main()
{
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    g.printSCCs();
    return 0;
}
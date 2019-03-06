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

    void topologicalSortUtil(int u, bool visited[], stack<int> &Stack)
    {
        visited[u] = true;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (!visited[v])
            {
                topologicalSortUtil(v, visited, Stack);
            }
        }

        Stack.push(u);
    }

    void topologicalSort()
    {
        stack<int> Stack;
        bool *visited = new bool[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                topologicalSortUtil(i, visited, Stack);
        }

        while (!Stack.empty())
        {
            cout << Stack.top() << " ";
            Stack.pop();
        }
        cout << endl;
    }
};

int main()
{
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Following is a Topological Sort of the given graph \n";
    g.topologicalSort();
    return 0;
}
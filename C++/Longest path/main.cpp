#include <iostream>
#include <vector>
#include <stack>
#include <limits.h>
using namespace std;

class AdjListNode
{
  public:
    int v, w;

    AdjListNode(int v, int w)
    {
        this->v = v;
        this->w = w;
    }
};

class Graph
{
  public:
    vector<AdjListNode> *adj;
    int V;
    Graph(int v)
    {
        V = v;
        adj = new vector<AdjListNode>[v];
    }

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back(AdjListNode(v, w));
    }

    void topologicalSortUtil(int u, bool visited[], stack<int> &Stack)
    {
        visited[u] = true;

        for (int i = 0; i < adj[u].size(); i++)
        {
            AdjListNode v = adj[u][i];
            if (!visited[v.v])
            {
                topologicalSortUtil(v.v, visited, Stack);
            }
        }

        Stack.push(u);
    }

    void longestPath(int s)
    {
        stack<int> Stack;
        bool *visited = new bool[V];
        int *dist = new int[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                topologicalSortUtil(i, visited, Stack);
        }

        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MIN;
        }

        dist[s] = 0;

        while (!Stack.empty())
        {
            int u = Stack.top();
            Stack.pop();

            if (dist[u] != INT_MIN)
                for (int i = 0; i < adj[u].size(); i++)
                {
                    AdjListNode v = adj[u][i];

                    if (dist[v.v] < dist[u] + v.w)
                    {
                        dist[v.v] = dist[u] + v.w;
                    }
                }
        }

        for (int i = 0; i < V; i++)
            if (dist[i] == INT_MIN)
                cout << "NINF"
                     << " ";
            else
                cout << dist[i] << " ";
        cout << endl;
    }
};

int main()
{
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int s = 1;
    cout << "Following are longest distances from "
            "source vertex "
         << s << " \n";
    g.longestPath(s);
    return 0;
}
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

class Edge
{
  public:
    int u, v;

    Edge(int i, int j)
    {
        u = i;
        v = j;
    }
};

class Graph
{
    int V, *disc, *low, *parent, time;
    stack<Edge> st;
    vector<int> *adj;

    void biconnectedUtil(int u)
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
                st.push(Edge(u, v));
                biconnectedUtil(v);

                low[u] = min(low[u], low[v]);

                if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]))
                {
                    while (st.top().u != u || st.top().v != v)
                    {
                        cout << st.top().u << "-" << st.top().v << " ";
                        st.pop();
                    }
                    cout << st.top().u << "-" << st.top().v << " ";
                    st.pop();
                    cout << endl;
                }
            }
            else if (v != parent[u])
            {
                low[u] = min(low[u], disc[v]);

                if (disc[v] < disc[u])
                {
                    st.push(Edge(u, v));
                }
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
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void printBCC()
    {
        // Init
        for (int i = 0; i < V; i++)
        {
            disc[i] = -1;
            low[i] = -1;
            parent[i] = -1;
        }
        time = 0;

        // Print biconnected components
        for (int i = 0; i < V; i++)
        {
            if (disc[i] == -1)
                biconnectedUtil(i);
        }

        // if edges remaining in stack
        while (!st.empty())
        {
            Edge e = st.top();
            st.pop();
            cout << e.u << "-" << e.v << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g(12);
    g.addEdge(0, 1);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 3);
    g.addEdge(3, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 2);
    g.addEdge(2, 4);
    g.addEdge(4, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 3);
    g.addEdge(1, 5);
    g.addEdge(5, 1);
    g.addEdge(0, 6);
    g.addEdge(6, 0);
    g.addEdge(5, 6);
    g.addEdge(6, 5);
    g.addEdge(5, 7);
    g.addEdge(7, 5);
    g.addEdge(5, 8);
    g.addEdge(8, 5);
    g.addEdge(7, 8);
    g.addEdge(8, 7);
    g.addEdge(8, 9);
    g.addEdge(9, 8);
    g.addEdge(10, 11);
    g.addEdge(11, 10);
    g.printBCC();
    return 0;
}
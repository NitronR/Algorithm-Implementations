#include <iostream>
#include <limits.h>
using namespace std;
#define V 5

int minKey(bool mstSet[], int key[])
{
    int min = INT_MAX, mind = 0;
    for (int i = 0; i < V; i++)
    {
        if (key[i] < min && !mstSet[i])
        {
            min = key[i];
            mind = i;
        }
    }

    return mind;
}

int *primsMST(int graph[V][V])
{
    int *parent = new int[V],
        *key = new int[V], u;

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX;

    bool *mstSet = new bool[V];
    for (int i = 0; i < V; i++)
        mstSet[i] = false;

    parent[0] = -1;
    key[0] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        u = minKey(mstSet, key);
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 && !mstSet[v] && key[v] > graph[u][v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    return parent;
}

void printMst(int graph[V][V])
{
    int *parent = primsMST(graph);

    cout << "MST: " << endl;
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << ", " << i << " : " << graph[i][parent[i]] << endl;
    }
}

int main()
{
    int graph[V][V] = {{0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0}};
    ;

    // Print the solution
    printMst(graph);
    return 0;
}
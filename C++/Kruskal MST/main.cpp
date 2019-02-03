#include <iostream>
#include <algorithm>
using namespace std;

class Edge
{
public:
  int src, dest, weight;
};

class Subset
{
public:
  int parent, rank;
};

bool compEdge(Edge e1, Edge e2)
{
  return e1.weight < e2.weight;
}

class Graph
{
public:
  int V, numEdges;
  Edge *edges;
  Graph(int v, int n)
  {
    edges = new Edge[n];
    V = v;
    numEdges = n;
  }

  void sortEdges()
  {
    sort(edges, edges + numEdges, compEdge);
  }
};

int find(Subset subsets[], int x)
{
  if (subsets[x].parent != x)
  {
    subsets[x].parent = find(subsets, subsets[x].parent);
  }
  return subsets[x].parent;
}

void Union(Subset subsets[], int u, int v)
{
  int x = find(subsets, u);
  int y = find(subsets, v);

  if (subsets[x].rank < subsets[y].rank)
  {
    subsets[x].parent = y;
  }
  else if (subsets[x].rank > subsets[y].rank)
  {
    subsets[y].parent = x;
  }
  else
  {
    subsets[y].parent = x;
    subsets[x].rank++;
  }
}

Edge *KruskalMST(Graph graph)
{
  graph.sortEdges();

  int e = 0, index = 0;
  Edge *MST = new Edge[graph.V - 1];
  Subset *subsets = new Subset[graph.V];

  for (int i = 0; i < graph.V; i++)
  {
    subsets[i].parent = i;
    subsets[i].rank = 0;
  }

  while (e < graph.V - 1)
  {
    int x = find(subsets, graph.edges[index].src);
    int y = find(subsets, graph.edges[index].dest);

    if (x != y)
    {
      MST[e++] = graph.edges[index];
      Union(subsets, x, y);
    }
    index++;
  }

  return MST;
}

int main()
{
  int V = 4; // Number of vertices in graph
  int E = 5; // Number of edges in graph
  Graph graph(V, E);

  // add edge 0-1
  graph.edges[0].src = 0;
  graph.edges[0].dest = 1;
  graph.edges[0].weight = 10;

  // add edge 0-2
  graph.edges[1].src = 0;
  graph.edges[1].dest = 2;
  graph.edges[1].weight = 6;

  // add edge 0-3
  graph.edges[2].src = 0;
  graph.edges[2].dest = 3;
  graph.edges[2].weight = 5;

  // add edge 1-3
  graph.edges[3].src = 1;
  graph.edges[3].dest = 3;
  graph.edges[3].weight = 15;

  // add edge 2-3
  graph.edges[4].src = 2;
  graph.edges[4].dest = 3;
  graph.edges[4].weight = 4;

  Edge *mst = KruskalMST(graph);

  cout << "MST: " << endl;
  for (int i = 0; i < graph.V - 1; i++)
  {
    cout << mst[i].src << "," << mst[i].dest << " w:" << mst[i].weight << endl;
  }
  return 0;
}
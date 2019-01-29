#include <iostream>
#include <string>
using namespace std;

class MinHeapNode
{
  public:
    char c;
    int freq;
    MinHeapNode *left, *right;

    MinHeapNode() {}
    MinHeapNode(char c, int freq, MinHeapNode *left = NULL, MinHeapNode *right = NULL)
    {
        this->c = c;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

class MinHeap
{
  public:
    MinHeapNode **nodes;
    int size, capacity;

    MinHeap(char data[], int freq[], int n)
    {
        size = capacity = n;
        nodes = new MinHeapNode *[size];

        for (int i = 0; i < n; i++)
            nodes[i] = new MinHeapNode(data[i], freq[i]);

        buildMinHeap();
    }

    MinHeapNode *extractMin()
    {
        MinHeapNode *min = nodes[0];
        nodes[0] = nodes[--size];

        minHeapify(0);
        return min;
    }

    void insert(MinHeapNode *node)
    {
        size++;
        int i = size - 1;

        while (i > 0 && (nodes[(i - 1) / 2]->freq > node->freq))
        {
            nodes[i] = nodes[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        nodes[i] = node;
    }

    void minHeapify(int i)
    {
        int smallest = i,
            left = 2 * i + 1,
            right = 2 * i + 2;
        if (left < size && nodes[left]->freq < nodes[smallest]->freq)
            smallest = left;
        if (right < size && nodes[right]->freq < nodes[smallest]->freq)
            smallest = right;
        if (smallest != i)
        {
            swap(nodes[i], nodes[smallest]);
            minHeapify(smallest);
        }
    }

    void buildMinHeap()
    {
        for (int i = (size - 1) / 2; i >= 0; i--)
        {
            minHeapify(i);
        }
    }

    bool isSizeOne()
    {
        return size == 1;
    }
};

class HuffmannTree
{
  public:
    MinHeap *tree;
    HuffmannTree(char data[], int freq[], int size)
    {
        MinHeapNode *a, *b;
        tree = new MinHeap(data, freq, size);

        while (!tree->isSizeOne())
        {
            a = tree->extractMin();
            b = tree->extractMin();

            tree->insert(new MinHeapNode('$', a->freq + b->freq, a, b));
        }
    }
    void printCodes()
    {
        cout << "Huffmann codes: " << endl;
        printCodesRecur(tree->nodes[0], "");
    }

    void printCodesRecur(MinHeapNode *node, string prevCode)
    {
        if (node->c != '$')
        {
            cout << node->c << ": " << prevCode << endl;
        }
        if (node->left != NULL)
            printCodesRecur(node->left, prevCode + "0");
        if (node->right != NULL)
            printCodesRecur(node->right, prevCode + "1");
    }
};

void huffmannCodes(char data[], int freq[], int size)
{
    HuffmannTree tree(data, freq, size);
    tree.printCodes();
}

int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmannTree tree(arr, freq, size);
    tree.printCodes();
    return 0;
}
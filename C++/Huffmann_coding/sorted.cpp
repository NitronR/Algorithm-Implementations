#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node
{
  public:
    char c;
    int freq;
    Node *left, *right;

    Node() {}
    Node(char c, int freq, Node *left = NULL, Node *right = NULL)
    {
        this->c = c;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

Node *findMin(queue<Node *> &first, queue<Node *> &second)
{
    Node *min;
    if (!first.empty() && first.front()->freq < second.front()->freq)
    {
        min = first.front();
        first.pop();
    }
    else
    {
        min = second.front();
        second.pop();
    }
    return min;
}

class HuffmannTree
{
  public:
    Node *tree;
    HuffmannTree(char data[], int freq[], int size)
    {
        Node *a, *b;
        queue<Node *> first, second;

        // add nodes to first queue
        for (int i = 0; i < size; i++)
        {
            first.push(new Node(data[i], freq[i]));
        }

        // do till first is empty and second has 1 element
        while (!(first.empty() && second.size() == 1))
        {
            a = findMin(first, second);
            b = findMin(first, second);

            second.push(new Node('$', a->freq + b->freq, a, b));
        }

        tree = second.front();
    }
    void printCodes()
    {
        cout << "Huffmann codes: " << endl;
        printCodesRecur(tree, "");
    }

    void printCodesRecur(Node *node, string prevCode)
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
    huffmannCodes(arr, freq, size);
    return 0;
}
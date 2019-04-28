#include <iostream>
using namespace std;

class Node
{
  public:
    int val;
    Node *left, *right;

    Node(int val)
    {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};

int vertexCoverCount(Node *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 0;

    int size_inc = 1 + vertexCoverCount(root->left) + vertexCoverCount(root->right);

    int size_exc = 0;

    if (root->left)
        size_exc += 1 + vertexCoverCount(root->left->left) + vertexCoverCount(root->left->right);

    if (root->left)
        size_exc += 1 + vertexCoverCount(root->right->left) + vertexCoverCount(root->right->right);

    return (size_exc < size_inc) ? size_exc : size_inc;
}

int main()
{
    Node *root = new Node(20);
    root->left = new Node(8);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);
    root->right = new Node(22);
    root->right->right = new Node(25);

    cout << vertexCoverCount(root) << endl;
    return 0;
}
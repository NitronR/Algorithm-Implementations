
// Array Utiliy
namespace ArrayUtils{
    void printArray(int[], int);
}

// Singly Linked List Utility
namespace LinkedListUtils
{
    class Node
    {
    public:
        int val;
        Node *next;
    };
    void printList(Node*);
    Node *getTail(Node*);
    void insertAtHead(Node**,int);
}
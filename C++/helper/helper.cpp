#include <iostream>
#include <math.h>
using namespace std;

// Array Utilities
namespace ArrayUtils
{
void printArray(int arr[], int n)
{
    cout << "Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
} // namespace ArrayUtils

// Singly Linked List Utilities
namespace LinkedListUtils
{
class Node
{
  public:
    int val;
    Node *next;
};
void printList(Node *head)
{
    cout << "Linked List: " << endl;
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}
Node *getTail(Node *curr)
{
    while (curr != NULL && curr->next != NULL)
        curr = curr->next;
    return curr;
}
void insertAtHead(Node **head, int val)
{
    Node *newNode = new Node;
    newNode->next = *head;
    newNode->val = val;
    (*head) = newNode;
}
} // namespace LinkedListUtils

// 2D Geometry Utilities
namespace Geom2DUtils
{
class Point
{
  public:
    float x, y;

    Point() { x = y = 0; };
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};
float dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
} // namespace Geom2DUtils

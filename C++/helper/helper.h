#include <math.h>

// Array Utiliy
namespace ArrayUtils
{
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
void printList(Node *);
Node *getTail(Node *);
void insertAtHead(Node **, int);
} // namespace LinkedListUtils

namespace Geom2DUtils
{
class Point
{
public:
  float x, y;
  Point();
  Point(float, float);
};

float dist(Point, Point);
} // namespace Geom2DUtils
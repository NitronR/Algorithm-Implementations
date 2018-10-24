#include <iostream>
using namespace std;

class Node
{
  public:
    int val;
    Node *next;
};

void split(Node *head, Node **a, Node **b)
{
    Node *slow = head, *fast = head->next;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    *a = head;
    *b = slow->next;
    slow->next = NULL;
}

Node *merge(Node *a, Node *b)
{
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    Node *result = NULL;

    if (a->val <= b->val)
    {
        result = a;
        result->next = merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}

void mergeSort(Node **headRef)
{
    Node *head = *headRef;
    if (head == NULL || head->next == NULL)
        return;

    Node *a, *b;
    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = merge(a, b);
}

void insertAtHead(Node **head, int val)
{
    Node *newNode = new Node;
    newNode->val = val;
    newNode->next = *head;
    *head = newNode;
}

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

int main()
{
    Node *a = NULL;

    insertAtHead(&a, 15);
    insertAtHead(&a, 10);
    insertAtHead(&a, 5);
    insertAtHead(&a, 20);
    insertAtHead(&a, 3);
    insertAtHead(&a, 2);

    printList(a);
    cout << "Sorting..." << endl;
    mergeSort(&a);
    printList(a);
    return 0;
}
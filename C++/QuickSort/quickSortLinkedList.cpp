#include <iostream>
#include "../helper/helper.h"
using namespace std;
using namespace LinkedListUtils;

Node *partition(Node *head, Node *end, Node **newHead, Node **newTail)
{
    Node *pivot = end, *cur = head, *prev = NULL, *tail = end;

    while (cur != pivot)
    {
        if (cur->val < pivot->val)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev != NULL)
                prev->next = cur->next;
            Node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newTail) = tail;

    return pivot;
}

Node *quickSortRecur(Node *head, Node *tail)
{
    if (head == NULL || head == tail)
        return head;
    Node *newHead = NULL, *newTail = NULL;
    Node *pivot = partition(head, tail, &newHead, &newTail);

    if (pivot != newHead)
    {
        Node *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecur(pivot->next, newTail);
    return newHead;
}

Node *quickSort(Node **head)
{
    (*head) = quickSortRecur(*head, getTail(*head));
}

int main()
{
    Node *list = NULL;

    insertAtHead(&list, 5);
    insertAtHead(&list, 4);
    insertAtHead(&list, 1);
    insertAtHead(&list, 3);
    insertAtHead(&list, 2);

    printList(list);
    cout << "Sorting..." << endl;
    quickSort(&list);
    printList(list);
    return 0;
}
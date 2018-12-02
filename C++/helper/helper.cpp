#include<iostream>
using namespace std;

// Array Utilities
namespace ArrayUtils{
    void printArray(int arr[], int n)
    {
        cout << "Array: ";
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
}

// Singly Linked List Utilities
namespace LinkedListUtils{
    class Node
    {
    public:
        int val;
        Node *next;
    };
    void printList(Node *head){
        cout << "Linked List: " << endl;
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    Node* getTail(Node *curr){
        while(curr!=NULL && curr->next!=NULL)
            curr = curr->next;
        return curr;
    }
}
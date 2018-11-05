#include <iostream>
#include "../helper/helper.h"
using namespace std;

// partitions array by first element
// returns position after placement
int partition(int arr[], int l, int r)
{
    int key = arr[l];
    int i = l + 1;

    for (int j = l + 1; j <= r; j++)
    {
        if (arr[j] < key)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[l], arr[i - 1]);
    return i - 1;
}

// sorts array from index l to r (both inclusive)
void quickSortIterative(int arr[], int l, int r)
{
    int *stack = new int[r - l + 1];
    int top = -1;

    stack[++top] = l;
    stack[++top] = r;
    while (top >= 0)
    {
        r = stack[top--];
        l = stack[top--];

        int i = partition(arr, l, r);

        if (i - 1 > l)
        {
            stack[++top] = l;
            stack[++top] = i - 1;
        }
        if (i + 1 < r)
        {
            stack[++top] = i + 1;
            stack[++top] = r;
        }
    }
}

int main()
{
    int arr[] = {5, 4, 1, 3, 2},
        n = 5;

    // printArray from helper
    printArray(arr, n);
    cout << "Sorting..." << endl;
    quickSortIterative(arr, 0, n - 1);
    printArray(arr, n);

    return 0;
}
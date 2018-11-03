#include <iostream>
#include "../helper.h"
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
void quickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int i = partition(arr, l, r);
        quickSort(arr, l, i - 1);
        quickSort(arr, i + 1, r);
    }
}

int main()
{
    int arr[] = {5, 4, 1, 3, 2},
        n = 5;

    // printArray from helper
    printArray(arr, n);
    cout << "Sorting..." << endl;
    quickSort(arr, 0, n - 1);
    printArray(arr, n);

    return 0;
}
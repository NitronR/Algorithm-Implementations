#include <iostream>
#include "../helper/helper.h"
using namespace std;
using ArrayUtils::printArray;

int partition(int arr[], int l, int r)
{
    int n = r - l + 1,
        pivot = (rand() % n) + l,
        x = arr[pivot],
        i = l + 1;

    swap(arr[l], arr[pivot]);

    for (int j = i; j <= r; j++)
    {
        if (arr[j] <= x)
        {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[l], arr[i - 1]);
    return i - 1;
}

int randomizedSelect(int arr[], int l, int r, int k)
{
    if (l <= r)
    {
        int pivot = (l == r) ? l : partition(arr, l, r);
        if (pivot == k - 1)
            return arr[pivot];

        int left = randomizedSelect(arr, l, pivot - 1, k);
        if (left != -1)
            return left;
        int right = randomizedSelect(arr, pivot + 1, r, k);
        if (right != -1)
            return right;
    }

    return -1;
}

int kthSmallest(int arr[], int n, int k)
{
    int *copy_arr = new int[n];
    copy(arr, arr + n, copy_arr);
    return randomizedSelect(copy_arr, 0, n - 1, k);
}

int main()
{
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]), k = 5;

    printArray(arr, n);
    cout << "5th smallest element is " << kthSmallest(arr, n, k);
    return 0;
}
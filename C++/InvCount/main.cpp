#include <iostream>
#include "../helper/helper.h"
using namespace std;
using ArrayUtils::printArray;

int merge(int arr[], int temp[], int left, int mid, int right)
{
    int i = left, j = mid, k = left, inv = 0;

    while ((i <= mid - 1) && (j <= right))
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            inv += (mid - i);
        }
    }

    while (i <= (mid - 1))
    {
        temp[k++] = arr[i++];
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }

    return inv;
}

int mergeSort(int arr[], int temp[], int left, int right)
{
    int inv = 0, mid;
    if (left < right)
    {
        mid = (left + right) / 2;

        inv = mergeSort(arr, temp, left, mid);
        inv += mergeSort(arr, temp, mid + 1, right);
        inv += merge(arr, temp, left, mid + 1, right);
    }
    return inv;
}

int mergeInvCount(int arr[], int size)
{
    int *temp = new int[size];
    return mergeSort(arr, temp, 0, size - 1);
}

int main()
{
    int arr[] = {1, 20, 6, 4, 5};

    printArray(arr, 5);

    cout << "Inversion count: " << mergeInvCount(arr, 6) << endl;

    return 0;
}
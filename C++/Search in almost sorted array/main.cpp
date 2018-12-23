#include <iostream>
#include "../helper/helper.h"
using namespace std;
using ArrayUtils::printArray;

int almostBinarySearch(int arr[], int l, int r, int x)
{
    if (l <= r)
    {
        int mid = (l + r) / 2;

        if (arr[mid] == x)
            return mid;
        if (mid > l && arr[mid - 1] == x)
            return mid - 1;
        if (mid < r && arr[mid + 1] == x)
            return mid + 1;

        if (arr[mid] > x)
            return almostBinarySearch(arr, l, mid - 2, x);
        return almostBinarySearch(arr, mid + 2, r, x);
    }
    return -1;
}

int main()
{
    int arr[] = {3, 2, 10, 4, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 4;
    int result = almostBinarySearch(arr, 0, n - 1, x);

    printArray(arr, n);
    cout << x << " found at index " << result << endl;
    return 0;
}
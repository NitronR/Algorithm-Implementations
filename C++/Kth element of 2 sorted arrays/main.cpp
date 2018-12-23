#include <iostream>
#include "../helper/helper.h"
using namespace std;
using ArrayUtils::printArray;

int kth(int arr1[], int arr2[], int m, int n, int k, int st1 = 0, int st2 = 0)
{
    if (st1 == m)
        return arr2[st2 + k - 1];
    if (st2 == n)
        return arr1[st1 + k - 1];

    if (k == 0 || k > (m - st1) + (n - st2))
        return -1;

    if (k == 1)
        return (arr1[st1] < arr2[st2]) ? arr1[st1] : arr2[st2];

    int curr = k / 2;
    if (curr - 1 >= (m - st1))
    {
        if (arr1[m - 1] < arr2[st2 + curr - 1])
            return arr2[st2 + (k - (m - st1)) - 1];
        else
            return kth(arr1, arr2, m, n, k - curr, st1, st2 + curr);
    }

    if (curr - 1 >= (n - st2))
    {
        if (arr2[n - 1] < arr1[st1 + curr - 1])
            return arr1[st1 + (k - (n - st2)) - 1];
        else
            return kth(arr1, arr2, m, n, k - curr, st1 + curr, st2);
    }

    if (arr1[st1 + curr - 1] > arr2[st2 + curr - 1])
        return kth(arr1, arr2, m, n, k - curr, st1, st2 + curr);
    else
        return kth(arr1, arr2, m, n, k - curr, st1 + curr, st2);
}

int main()
{
    int arr1[5] = {2, 3, 6, 7, 9};
    int arr2[4] = {1, 4, 8, 10};
    int k = 5;

    printArray(arr1, 5);
    printArray(arr2, 4);

    cout << "The fifth element is: " << kth(arr1, arr2, 5, 4, k) << endl;
    return 0;
}
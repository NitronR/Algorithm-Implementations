#include <iostream>
#include <algorithm>
using namespace std;

int median(int arr[], int n)
{
    if (n % 2 == 0)
        return (arr[n / 2] + arr[n / 2 - 1]) / 2;
    return arr[n / 2];
}

int getMedian(int arr1[], int arr2[], int n)
{
    if (n <= 0)
        return -1;
    if (n == 1)
        return (arr1[0] + arr2[0]) / 2;
    if (n == 2)
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;

    int m1 = median(arr1, n), m2 = median(arr2, n);

    if (m1 == m2)
        return m1;

    if (m1 < m2)
    {
        if (n % 2 == 0)
            return getMedian(arr1 + n / 2 - 1, arr2, n / 2 + 1);
        return getMedian(arr1 + n / 2, arr2, n - n / 2);
    }

    if (n % 2 == 0)
        return getMedian(arr2 + n / 2 - 1, arr1, n / 2 + 1);
    return getMedian(arr2 + n / 2, arr1, n / 2);
}

int main()
{
    int ar1[] = {1, 2, 3, 6};
    int ar2[] = {4, 6, 8, 10};
    int n = 4;
    cout << "Median is " << getMedian(ar1, ar2, n) << endl;
    return 0;
}
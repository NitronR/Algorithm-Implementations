#include <iostream>
#include <queue>
#include <vector>
#include "../helper/helper.h"
using namespace std;
using ArrayUtils::printArray;

void sortK(int arr[], int n, int k)
{
    priority_queue<int, vector<int>, greater<int>> q(arr, arr + k + 1);

    int index = 0;
    for (int i = 0; i < n - k - 1; i++)
    {
        arr[index++] = q.top();
        q.pop();
        q.push(arr[k + i + 1]);
    }

    while (!q.empty())
    {
        arr[index++] = q.top();
        q.pop();
    }
}

int main()
{
    int k = 3;
    int arr[] = {2, 6, 3, 12, 56, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, n);

    sortK(arr, n, k);
    cout << "Sorting..." << endl;
    printArray(arr, n);
    return 0;
}
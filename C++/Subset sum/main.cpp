#include <iostream>
using namespace std;

bool isSubsetSum(int set[], int n, int sum)
{
    int **s = new int *[n + 1];

    for (int i = 0; i <= n; i++)
    {
        s[i] = new int[sum + 1];
        s[i][0] = true;
    }

    for (int i = 0; i <= sum; i++)
    {
        s[0][i] = false;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (set[i - 1] > j)
            {
                s[i][j] = s[i - 1][j];
            }
            else
            {
                s[i][j] = s[i - 1][j] || s[i - 1][j - set[i - 1]];
            }
        }
    }

    return s[n][sum];
}

int main()
{
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(set) / sizeof(set[0]);
    if (isSubsetSum(set, n, sum))
        cout << "Found a subset with given sum" << endl;
    else
        cout << "No subset with given sum" << endl;
    return 0;
}
#include <iostream>
using namespace std;

typedef long long llong;

llong countInc(int n)
{
    int **dp = new int *[10];

    for (int i = 0; i < 10; i++)
    {
        dp[i] = new int[n + 1];
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;
        dp[i][1] = 1;
    }

    for (int digit = 0; digit <= 9; digit++)
    {
        for (int len = 2; len <= n; len++)
        {
            for (int x = 0; x <= digit; x++)
            {
                dp[digit][len] += dp[x][len - 1];
            }
        }
    }

    llong count = 0;

    for (int i = 0; i <= 9; i++)
    {
        count += dp[i][n];
    }

    return count;
}

int main()
{
    int n = 3;
    cout << countInc(n);
    return 0;
}
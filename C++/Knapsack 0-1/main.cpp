#include <iostream>
using namespace std;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int knapsack(int val[], int w[], int n, int W)
{
    int **K = new int *[n + 1];

    for (int i = 0; i <= n; i++)
    {
        K[i] = new int[W + 1];
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0)
                K[i][j] = 0;
            else if (j >= w[i])
                K[i][j] = max(val[i] + K[i - 1][j - w[i]], K[i - 1][j]);
            else
                K[i][j] = K[i - 1][j];
        }
    }

    return K[n][W];
}

int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    cout << knapsack(val, wt, n, W) << endl;
    return 0;
}
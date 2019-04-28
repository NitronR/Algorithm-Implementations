#include <iostream>
using namespace std;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int minCost(int **cost, int n, int m)
{
    int **t = new int *[n + 1];

    for (int i = 0; i <= n; i++)
        t[i] = new int[m + 1];

    t[0][0] = cost[0][0];

    for (int i = 1; i <= n; i++)
        t[i][0] = t[i - 1][0] + cost[i][0];

    for (int i = 1; i <= m; i++)
        t[0][i] = t[0][i - 1] + cost[0][i];

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            t[i][j] = min(t[i - 1][j - 1], min(t[i - 1][j], t[i][j - 1])) + cost[i][j];
        }
    }

    return t[n][m];
}

int main()
{
    int **cost = new int *[3];

    for (int i = 0; i < 3; i++)
        cost[i] = new int[3];

    cost[0][0] = 1;
    cost[0][1] = 2;
    cost[0][2] = 3;

    cost[1][0] = 4;
    cost[1][1] = 8;
    cost[1][2] = 2;

    cost[2][0] = 1;
    cost[2][1] = 5;
    cost[2][2] = 3;

    cout << minCost(cost, 2, 2) << endl;
    return 0;
}
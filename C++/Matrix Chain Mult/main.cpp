#include <iostream>
#include <limits.h>
using namespace std;

int MatrixChainMult(int *p, int n)
{
    int q, **m;

    m = new int *[n];

    for (int i = 0; i < n; i++)
    {
        m[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        m[i][i] = 0;
    }

    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;

            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                }
            }
        }
    }

    return m[1][n - 1];
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Minimum number of multiplications is " << MatrixChainMult(arr, size) << endl;
    return 0;
}
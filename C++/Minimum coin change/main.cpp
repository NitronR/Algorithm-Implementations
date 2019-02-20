#include <iostream>
#include <vector>
using namespace std;

int deno[] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
int n = sizeof(deno) / sizeof(deno[0]);

vector<int> findMin(int amount)
{
    vector<int> ans;

    for (int i = n - 1; i >= 0; i--)
    {
        while (amount >= deno[i])
        {
            amount -= deno[i];
            ans.push_back(deno[i]);
        }
    }

    return ans;
}

int main()
{
    int amount = 93;

    vector<int> minChange = findMin(amount);

    cout << "Minimum change required: ";

    for (int i = 0; i < minChange.size(); i++)
    {
        cout << minChange[i] << " ";
    }
    cout << endl;
    return 0;
}
#include <iostream>
#include <algorithm>
#include "../helper/helper.h"
using namespace std;
class Point
{
  public:
    float x, y;

    Point() { x = y = 0; };
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

float dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int compareX(Point P1, Point P2)
{
    return P1.x < P2.x;
}

int compareY(Point P1, Point P2)
{
    return P1.y < P2.y;
}

float bruteClosest(Point P[], int n)
{
    float min = -1, d;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            d = dist(P[i], P[j]);
            if (min == -1 || (min > d))
            {
                min = d;
            }
        }
    }
    if (min == -1)
        min = 0;
    return min;
}

float stripClosest(Point P[], int n, int d)
{
    float min = d, dt;
    sort(P, P + n, compareY);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n && (P[j].y - P[i].y < min); j++)
        {
            dt = dist(P[i], P[j]);
            if (dt < min)
                min = dt;
        }
    }

    return min;
}

float closestUtil(Point P[], int n)
{
    if (n <= 3)
        return bruteClosest(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    float dl = closestUtil(P, mid), dr = closestUtil(P + mid, n - mid);

    float d = min(dl, dr);

    Point *strip = new Point[n];
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (abs(midPoint.x - P[i].x) < d)
            strip[j++] = P[i];
    }

    return stripClosest(strip, j, d);
}

float closest(Point P[], int n)
{
    sort(P, P + n, compareX);

    return closestUtil(P, n);
}

int main()
{
    Point P[6];
    P[0] = Point(2, 3);
    P[1] = Point(12, 30);
    P[2] = Point(40, 50);
    P[3] = Point(5, 1);
    P[4] = Point(12, 10);
    P[5] = Point(3, 4);
    int n = sizeof(P) / sizeof(P[0]);

    cout << "Minimum distance: " << closestUtil(P, n) << endl;
    return 0;
}
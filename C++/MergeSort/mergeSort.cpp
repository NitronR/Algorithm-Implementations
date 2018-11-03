#include <iostream>
#include "../helper.h"
using namespace std;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k, n1 = m - l + 1, n2 = r - m,
     *L=new int[n1], *R=new int[n2];

     for(int i=0;i<n1;i++) L[i]=arr[i+l];
     for(int i=0;i<n2;i++) R[i]=arr[i+m+1];
     
     i=j=0;
     k=l;
     while(i<n1 && j<n2){
         if(L[i]<=R[j])
             arr[k]=L[i++];
         else
             arr[k]=R[j++];
         k++;
     }
     while(i<n1) arr[k++]=L[i++];
     while(j<n2) arr[k++]=R[j++];
}


void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, n);
    cout << "Sorting..." << endl;
    mergeSort(arr, 0, n - 1);
    printArray(arr, n);
    return 0;
}

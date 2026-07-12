#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int> &arr, int n)
{
  for (int i = 1; i < n; i++)
  {
    int k = i;
    for (int j = k - 1; j >= 0; j--)
    {
      if (arr[k] < arr[j])
      {
        swap(arr[j], arr[k]);
        k--;
      }
    }
  }
}

int main(int argc, char const *argv[])
{
  vector<int> arr = {2, 4, 6, 8, 3};

  insertionSort(arr, 5);

  for (auto i : arr)
  {
    cout << i << "\t";
  }
  return 0;
}
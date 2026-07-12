#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int beautifulArray(vector<int> &arr)
{
  int n = arr.size();
  vector<pair<int, int>> sorted(n);

  for (int i = 0; i < n; i++)
  {
    sorted[i] = {arr[i], i};
  }
  sort(sorted.begin(), sorted.end());

  vector<bool> visited(n, false);

  int swaps = 0;

  for (int i = 0; i < n; i++)
  {
    if (visited[i] || sorted[i].second == i)
      continue;

    int cycleSize = 0;
    int j = 0;

    while(!visited[j]) {
      visited[j] = true;
      j = sorted[j].second;

      cycleSize++;
    }
    if(cycleSize > 1) swaps += cycleSize - 1;
  }
  return swaps;
}

int main(int argc, char const *argv[])
{
  vector<int> arr = {1, 12, 7, 15};
  return 0;
}
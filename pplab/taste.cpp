#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int maxTastePoints(int n, int m, vector<int> &v, vector<int> &d)
{
  priority_queue<pair<int, int>> pq;
  vector<int> times(n, 0);
  for (int i = 0; i < n; i++)
    pq.push({v[i], i});

  int points = 0;
  for (int i = 0; i < m; i++)
  {
    pair<int, int> topPair = pq.top();
    int tp = topPair.first, idx = topPair.second;
    pq.pop();
    points += tp;
    times[idx]++;
    tp = tp - d[idx] * times[idx];
    pq.push({tp, idx});
  }

  return points;
}

int main(int argc, char const *argv[])
{
  vector<int> v = {5, 7, 9};
  vector<int> d = {2, 4, 6};

  cout << maxTastePoints(3, 5, v, d);
  return 0;
}
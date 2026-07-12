#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int binaryKnapsack(vector<vector<int>> knapsack, int weight)
{
  int n = knapsack.size();
  vector<vector<int>> table(n + 1, vector<int>(weight + 1, 0));

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= weight; j++)
    {
      if (j - knapsack[i - 1][0] >= 0)
      {
        table[i][j] = max((table[i - 1][j]), (table[i - 1][j - knapsack[i - 1][0]] + knapsack[i - 1][1]));
      }
      else
      {
        table[i][j] = table[i - 1][j];
      }
    }
  }
  return table[n][weight];
}

int main(int argc, char const *argv[])
{
  vector<vector<int>> knapsack;
  int n, w;
  cout << "Enter knapsack size :" << endl;
  cin >> w;
  cout << "Enter how many houses are there :" << endl;
  cin >> n;
  int weight, profit;
  cout << "Enter each house's loot's weight and profit :" << endl;
  for (int i = 0; i < n; i++)
  {
    cout << "House " << i + 1 << " loot's weight and profit: ";
    cin >> weight >> profit;
    knapsack.push_back({weight, profit});
  }

  cout << "Maximum profit attained : " << binaryKnapsack(knapsack, w);
  return 0;
}
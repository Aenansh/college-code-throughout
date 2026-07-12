#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(string s)
{
  int m = s.length();
  int n = m - 1;
  vector<vector<int>> table(m, vector<int>(m, 0));
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (s[n - i] == s[j])
      {
        table[i][j] = 1;
      }
    }
  }

  for(auto i : table) {
    for(auto j : i) {
      cout << j << "\t";
    }
    cout << endl;
  }
  string ans = "";
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < m; j++)
    {
      string chk = "";
      int k = i, l = j;
      while (k < m && l < m)
      {
        if (table[k][l] == 1)
        {
          chk += s[n - k];
          cout << chk << endl;
          k++, l++;
        }
        else
          break;
      }
      cout << "chk : "<< i << " " << j << " : " << chk << endl;
      if (chk.length() > ans.length())
      {
        ans = chk;
      }
    }
  }
  return ans;
}

int main(int argc, char const *argv[])
{
  longestPalindrome("aacabdkacaa");
  return 0;
}
#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

#pragma region SERVERUPDATECALC
long serverUpdate(int u1, int r1, int u2, int r2)
{
  vector<long> s1Time;
  vector<long> s2Time;

  for (long i = 1; i <= ((u1 + u2) * 2); i++)
  {
    if (i % r1 != 0)
      s1Time.push_back(i);
    if (i % r2 != 0)
      s2Time.push_back(i);
  }

  int i = 0, j = 0;

  while ((u1 && u2) && (i < s1Time.size() && j < s2Time.size()))
  {
    if (s1Time[i] != s2Time[j])
    {
      if (s1Time[i] > s2Time[j])
      {
        u2--;
        j++;
      }
      else
      {
        u1--;
        i++;
      }
    }
    else
    {
      u1 >= u2 ? u1-- : u2--;
      i++, j++;
    }
  }

  while (u1 && i < s1Time.size())
  {
    u1--;
    i++;
  }

  while (u2 && j < s2Time.size())
  {
    u2--;
    j++;
  }

  return s1Time[i - 1] > s2Time[j - 1] ? s1Time[i - 1] : s2Time[j - 1];
}
#pragma endregion

int main(int argc, char const *argv[])
{
  cout << serverUpdate(50, 15, 60, 20);
  return 0;
}
#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int binaryToDecimal(string bin)
{
  int res = 0;
  for (char &b : bin)
  {
    if (b == '0' && res == 0)
      continue;
    else if (b == '1' && res == 0)
      res = 1;
    else if (b == '1' && res != 0)
      res = res * 2 + 1;
    else if (b == '0' && res != 0)
      res = res * 2;
  }
  cout << res << endl;
  return res;
}

string decimalToBinary(int num)
{
  string res = "";
  while (num > 0)
  {
    int bit = num % 2;
    res += to_string(bit);
    num /= 2;
  }

  reverse(res.begin(), res.end());
  cout << res << endl;
  return res;
}

string findDifferentBinaryString(vector<string> &nums)
{
  int n = nums.size();
  if (n == 1)
    return nums[0] == "0" ? "1" : "0";

  int vals = pow(2, n);
  unordered_map<int, int> dec;
  for (int i = 0; i < vals; i++)
  {
    dec[i] = 0;
  }

  for (auto &bin : nums)
  {
    int nm = binaryToDecimal(bin);
    cout << "Converted" << nm << endl;
    if (!dec[nm])
      dec[nm] = 1;
  }

  for (auto i : dec)
  {
    if (i.second == 0)
    {
      cout << "Missing" << i.first << endl;
      string ans = decimalToBinary(i.first);
      cout << "Answer" << ans << endl;
      return ans;
    }
  }

  return "";
}

int main(int argc, char const *argv[])
{
  vector<string> s = {"000", "101", "111"};
  cout << findDifferentBinaryString(s);
  return 0;
}
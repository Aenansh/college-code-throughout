#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int lexicographic_sort(string &a, string &b)
{
  return a.compare(b) < 0;
}

int lexicographic_sort_reverse(string &a, string &b)
{
  return a.compare(b) > 0;
}

int sort_by_no_of_distinct_chars(string &a, string &b)
{
  unordered_set<char> s1(a.begin(), a.end());
  int s1size = s1.size();

  unordered_set<char> s2(b.begin(), b.end());
  int s2size = s2.size();

  if(s1size == s2size) {
    return lexicographic_sort(a, b);
  }
  return s1size < s2size;
}

int sort_by_length(string &a, string &b)
{
  return a.length() < b.length();
}

void string_sort(vector<string> &arr, int n, int (&cmp_func)(string &a, string &b))
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (!cmp_func(arr[i], arr[j]))
        swap(arr[i], arr[j]);
    }
  }
}

int main(int argc, char const *argv[])
{
  vector<string> arr = {"wkue", "qoi", "sbv", "fekls"};

  string_sort(arr, 4, sort_by_no_of_distinct_chars);

  for(auto s: arr) {
    cout << s << "\t";
  }
  return 0;
}
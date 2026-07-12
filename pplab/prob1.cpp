#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

string find(vector<int> nums, int target)
{
  for (auto i : nums)
  {
    if (i == target)
      return "YES";
  }
  return "NO";
}

vector<vector<int>> makePair(vector<int> nums)
{
  if (nums.size() < 2)
    return {};
  sort(nums.begin(), nums.end());
  unordered_map<int, int> table;
  for (auto i : nums)
    table[i]++;

  vector<vector<int>> ans;
  for (auto i : nums)
  {
    if (table[i] && table[(-i)] && i != -i)
    {
      ans.push_back({i, -i});
      table[i] = 0;
      table[-i] = 0;
    }
    else
    {
      table[i] = 0;
    }
  }
  return ans;
}

vector<vector<int>> twoSum(vector<int> &nums, int target)
{
  vector<vector<int>> ans;
  unordered_map<int, int> table;
  for (auto i : nums)
  {
    table[i]++;
  }

  for (int i = 0; i < nums.size(); i++)
  {
    int diff = target - nums[i];
    if (diff == nums[i] && (table[diff] && table[diff] > 1))
      continue;
    if (table[diff])
    {
      ans.push_back({nums[i], diff});
      table[nums[i]] = 0;
      table[diff] = 0;
    }
  }
  return ans;
}

int partition(vector<int> &nums, int low, int high)
{
  int k = high;
  int pivot = nums[low];

  for (int i = high; i >= low; i--)
  {
    if (nums[i] > pivot)
    {
      swap(nums[k--], nums[i]);
    }
  }
  swap(nums[k], nums[low]);
  return k;
}

void quickSort(vector<int> &nums, int low, int high)
{
  if (low >= high)
    return;

  int pivot = partition(nums, low, high);
  quickSort(nums, low, pivot - 1);
  quickSort(nums, pivot + 1, high);
}

void runFindFunction()
{
  cout << "-----------------Find------------------------" << endl;
  vector<int> arr1;
  int n;
  cout << "Enter the size for the array... ";
  cin >> n;
  cout << "Enter values to the array..." << endl;
  for (int i = 0; i < n; i++)
  {
    int j;
    cin >> j;
    arr1.push_back(j);
  }
  int t;
  cout << "Enter the target... ";
  cin >> t;
  cout << find(arr1, t) << endl;
  cout << "------------------end------------------------" << endl;
}

void runMakePairFunction()
{
  cout << "-----------------make pair------------------------" << endl;
  vector<int> arr1;
  int n;
  cout << "Enter the size for the array... ";
  cin >> n;
  cout << "Enter values to the array..." << endl;
  for (int i = 0; i < n; i++)
  {
    int j;
    cin >> j;
    arr1.push_back(j);
  }
  vector<vector<int>> arr3 = makePair(arr1);

  for (auto i : arr3)
  {
    cout << i[0] << "," << i[1] << "\t";
  }
  cout << endl;
  cout << "--------------------end---------------------------" << endl;
}

void runTwoSumFunction()
{
  cout << "-----------------two sum------------------------" << endl;
  vector<int> arr1;
  int n;
  cout << "Enter the size for the array... ";
  cin >> n;
  cout << "Enter values to the array..." << endl;
  for (int i = 0; i < n; i++)
  {
    int j;
    cin >> j;
    arr1.push_back(j);
  }
  int t;
  cout << "Enter the target... ";
  cin >> t;
  vector<vector<int>> arr3 = twoSum(arr1, t);

  for (auto i : arr3)
  {
    cout << i[0] << "," << i[1] << "\t";
  }
  cout << endl;
  cout << "--------------------end---------------------------" << endl;
}

void runQuickSortFunction()
{
  cout << "-----------------quick sort------------------------" << endl;
  vector<int> arr1;
  int n;
  cout << "Enter the size for the array... ";
  cin >> n;
  cout << "Enter values to the array..." << endl;
  for (int i = 0; i < n; i++)
  {
    int j;
    cin >> j;
    arr1.push_back(j);
  }
  quickSort(arr1, 0, arr1.size() - 1);
  for (auto i : arr1)
    cout << i << "\t";
  cout << endl;
  cout << "---------------------end---------------------------" << endl;
}

int main(int argc, char const *argv[])
{
  runFindFunction();
  runMakePairFunction();
  runQuickSortFunction();
  runTwoSumFunction();
  return 0;
}
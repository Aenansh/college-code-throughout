#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

unordered_map<string, char> binToHex = {
    {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'}, {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'}};

void twosComplement(string &binary)
{
  int n = binary.length();
  for (int i = 0; i < n; i++)
  {
    binary[i] = binary[i] == '1' ? '0' : '1';
  }
  if (binary[n - 1] == '0')
  {
    binary[n - 1] = '1';
    return;
  }
  char carry = '1';
  binary[n - 1] = '0';
  for (int i = n - 2; i >= 0; i--)
  {
    if (binary[i] == '1')
      binary[i] = '0';
    else
    {
      binary[i] = '1';
      break;
    }
  }
}

string toHex(int num)
{
  string binary(32, '0');
  bool neg = false;
  if (num < 0)
  {
    neg = true;
    num = abs(num);
  }

  int idx = 31;
  while (num > 0)
  {
    int bit = num & 1;
    binary[idx] = '0' + bit;
    num = num >> 1;
    idx--;
  }
  if (neg)
  {
    twosComplement(binary);
  }
  string hexa;
  bool zeros = true;
  for (int i = 0; i <= 28; i += 4)
  {
    string bits;
    for (int j = 0; j <= 3; j++)
    {
      bits.push_back(binary[i + j]);
    }
    if (bits == "0000" && zeros)
      continue;
    hexa.push_back(binToHex[bits]);
  }
  return hexa;
}

int main(int argc, char const *argv[])
{
  cout << toHex(2);
  return 0;
}
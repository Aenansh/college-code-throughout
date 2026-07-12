#include <iostream>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

void printBoard(vector<vector<int>> board)
{
  for (auto i : board)
  {
    for (auto j : i)
    {
      if (j == 0)
        cout << ".\t";
      else
        cout << "Q\t";
    }
    cout << endl;
  }
}

bool isSafe(vector<vector<int>> &board, int row, int col)
{
  int n = board.size();

  for (int i = 0; i < col; i++)
  {
    if (board[row][i] == 1)
      return false;
  }

  for (int i = row, j = col; i >= 0, j >= 0; i--, j--)
  {
    if (board[i][j] == 1)
      return false;
  }

  for (int i = row, j = col; j >= 0 && i < n; i++, j--)
  {
    if (board[i][j] == 1)
      return false;
  }
  return true;
}

bool nQueens(vector<vector<int>> &board, int col)
{
  int n = board.size();
  if (n == 1)
  {
    board.push_back({1});
    return true;
  };
  if (n <= 3)
    return false;

  if (col >= n)
    return true;

  for (int i = 0; i < n; i++)
  {
    if (isSafe(board, i, col))
    {
      board[i][col] = 1;

      if (nQueens(board, col + 1))
      {
        return true;
      }

      board[i][col] = 0;
    }
  }
  return true;
}

int main(int argc, char const *argv[])
{

  return 0;
}
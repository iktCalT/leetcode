#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>> &board) {
    if (board.size() != 9 || board[0].size() != 9) {
      throw std::runtime_error("main: invalid argument");
    }

    // don't combine isRowValid(board, i, 0) with isRowValid(board, i, 1)
    // to make use of spacial locality
    for (int i = 0; i < 9; i++) {
      if (!isRowValid(board, i, 0)) {
        return false;
      }
    }

    for (int i = 0; i < 9; i++) {
      if (!isRowValid(board, i, 1)) {
        return false;
      }
    }

    for (int i = 0; i + 2 < 9; i += 3) {
      for (int j = 0; j + 2 < 9; j += 3) {
        if (!isSubboxValid(board, i, j)) {
          return false;
        }
      }
    }

    return true;
  }

private:
  bool isRowValid(std::vector<std::vector<char>> &board, int rowNo,
                  bool direction) {
    // direction = 0: row; direction = 1: col
    std::array<int, 9> arr;
    std::fill(arr.begin(), arr.end(), 0);
    for (int i = 0; i < 9; i++) {
      char c = direction ? board[rowNo][i] : board[i][rowNo];
      if (c - '0' > 9 || c - '0' < 1) {
        continue;
      }
      if (std::find(arr.begin(), arr.end(), c) != arr.end()) {
        return false;
      }
      arr[i] = c;
    }
    return true;
  }

  bool isSubboxValid(std::vector<std::vector<char>> &board, int rowNo,
                     int colNo) {
    std::array<int, 9> arr;
    std::fill(arr.begin(), arr.end(), 0);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        char c = board[rowNo + i][colNo + j];
        if (c - '0' > 9 || c - '0' < 1) {
          continue;
        }
        if (std::find(arr.begin(), arr.end(), c) != arr.end()) {
          return false;
        }
        arr[3 * i + j] = c;
      }
    }
    return true;
  }
};

int main() {
  Solution demo;
  std::vector<std::vector<char>> board;
  board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
           {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
           {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
           {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
           {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
           {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
           {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
           {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
           {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  std::cout << demo.isValidSudoku(board) << std::endl;

  board = {{'.', '.', '.', '.', '5', '.', '.', '1', '.'},
           {'.', '4', '.', '3', '.', '.', '.', '.', '.'},
           {'.', '.', '.', '.', '.', '3', '.', '.', '1'},
           {'8', '.', '.', '.', '.', '.', '.', '2', '.'},
           {'.', '.', '2', '.', '7', '.', '.', '.', '.'},
           {'.', '1', '5', '.', '.', '.', '.', '.', '.'},
           {'.', '.', '.', '.', '.', '2', '.', '.', '.'},
           {'.', '2', '.', '9', '.', '.', '.', '.', '.'},
           {'.', '.', '4', '.', '.', '.', '.', '.', '.'}};
  std::cout << demo.isValidSudoku(board) << std::endl;
}
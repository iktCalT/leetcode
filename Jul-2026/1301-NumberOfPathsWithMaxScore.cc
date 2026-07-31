#include <vector>

using namespace std;

class Solution {
private:
  const int m = 1e9 + 7;

  struct Cell {
    int max_sum; // maximum sum
    int mul;  // multiple
  };

public:
  vector<int> pathsWithMaxScore(vector<string>& board) {
    int n = board.size(); // a n * n board
    vector<vector<Cell>> dp (n + 1, 
                vector<Cell>(n + 1, {0, 0}));
    dp[n][n].mul = 1;
    //  p: padding
    //  4  3  2  1  0  p
    //  3  3  2  1  0  p
    //  2  2  2  1  0  p
    //  1  1  1  1  0  p
    //  0  0  0  0  0  p
    //  p  p  p  p  p  p
    for (int i = 0; i < n; ++i) {
      int bound = n - 1 - i;
      int r, c;
      // Row
      r = bound;
      for (int c = bound; c >= 0; --c) {
        int val = char2val(board[r][c]);
        move(r, c, val, dp);
      }
      // Col
      c = bound;
      for (int r = bound; r >= 0; --r) {
        int val = char2val(board[r][c]);
        move(r, c, val, dp);
      }
    }

    return {dp[0][0].max_sum, dp[0][0].mul};
  }

private:
  // character to value (if is obstacle, return -1)
  inline int char2val(const char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'X') return -1;
    return 0;
  }

  // move to r, c and modify dp[r][c] 
  void move(const int r, const int c, 
      const int val, vector<vector<Cell>>& dp) {
    if (val == -1) return; // obstacle

    int max_presum = max(dp[r][c+1].max_sum, 
          max(dp[r+1][c+1].max_sum, dp[r+1][c].max_sum));

    int mul = dp[r][c+1].max_sum == max_presum 
        ? dp[r][c+1].mul
        : 0;
    mul = dp[r+1][c+1].max_sum == max_presum 
        ? (mul + dp[r+1][c+1].mul) % m
        : mul;
    mul = dp[r+1][c].max_sum == max_presum 
        ? (mul + dp[r+1][c].mul) % m
        : mul;

    // When mul == 0, you cannot put max_sum in this cell.
    // Otherwise, it will eliminate other paths later
    if (mul == 0) return; 

    dp[r][c] = {max_presum + val, mul};
  }
};
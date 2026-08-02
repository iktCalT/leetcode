#include <iostream>
#include <vector>
using namespace std;

/* 
  Approach 2: Mathematical
  Intuition and Algorithm

  Alice clearly always wins the 2 pile game. With some effort, we can see that she always wins the 4 pile game.

  If Alice takes the first pile initially, she can always take the third pile. If she takes the fourth pile initially, she can always take the second pile. At least one of first + third, second + fourth is larger, so she can always win.

  We can extend this idea to N piles. Say the first, third, fifth, seventh, etc. piles are white, and the second, fourth, sixth, eighth, etc. piles are black. Alice can always take either all white piles or all black piles, and one of the colors must have a sum number of stones larger than the other color.

  Hence, Alice always wins the game.

  class Solution {
  public:
      bool stoneGame(vector<int>& piles) {
          return true;
      }
  };
 */

/* 14ms */
class Solution {
public:
  bool stoneGame(vector<int>& piles) {
    // BFS + truncate (DP)
    // sum(piles[i]) <= 500 * 500 < INT_MAX
    int n = piles.size();
    // dp[i][j]: maximum (i + j == odd, after Alice's turn) 
    // or minimum (i + j == even, after Bob's turn) net stones
    // (number of Alice's stones - number of Bob's stones),
    // where i is start, j is n - end
    vector<vector<int>> dp (n + 1); // A (n + 1) * (n + 1) triangle
    for (int i = 0; i < n + 1; ++i) {
      int m = n + 1 - i;
      dp[i] = vector<int>(m);
      for (int j = 0; j < m; ++j) {
        dp[i][j] = (i + j) % 2 ? INT_MIN : INT_MAX;
      }
    }
    dp[0][0] = 0;
    
    // sum == i + j. start < end => i + j < n
    for (int sum = 0; sum < n; ++sum) {
      for (int i = 0; i <= sum; ++i) {
        oneStep(i, sum - i, piles, dp);
      }
    }

    for (int i = 0; i < n + 1; ++i) {
      // after last step: end == start -> i + j == n
      // from [0][n] to [n][0]
      if (dp[i][n - i] > 0) return true;
    }

    return false;
  }

private: 
  void oneStep(int i, int j, const vector<int>& piles, 
               vector<vector<int>>& dp) {
    // Only consider [start, end) of piles, where
    // start = i, end = n - j. start < end => i + j < n
    int start = i;
    int end = piles.size() - j;
    if ((i + j) % 2 == 0) {
      // Alice's turn
      // Go right => ++j <=> --end
      dp[i][j+1] = max(dp[i][j+1], dp[i][j] + piles[end - 1]);
      // Go down => ++i <=> ++start
      dp[i+1][j] = max(dp[i+1][j], dp[i][j] + piles[start]);
    } else {
      // Bob's turn
      // Go right => ++j <=> --end
      dp[i][j+1] = min(dp[i][j+1], dp[i][j] - piles[end - 1]);
      // Go down => ++i <=> ++start
      dp[i+1][j] = min(dp[i+1][j], dp[i][j] - piles[start]);
    }
  }
};

/* Time Limit Exceeded */
class Solution0 {
public:
  bool stoneGame(vector<int>& piles) {
    // DFS
    // sum(piles[i]) <= 500 * 500 < INT_MAX
    return stoneGame(0, 0, 0, piles.size(), piles);
  }

private: 
  bool stoneGame(int net, bool who, int start, int end, const vector<int>& piles) {
    // Only consider [start, end) of piles
    // net: number of Alice's stones - number of Bob's stones
    // who: 0 -> Alice, 1 -> Bob
    // return 1 if Alice wins
    if (who == 0) {
      // Alice's turn
      if (end - start == 1) { // actually, this case should not happen, 
                               // because piles.length is even.
        return net + piles[start] > 0;
      } else {
        return stoneGame(net + piles[start], 1, start + 1, end, piles)
            || stoneGame(net + piles[end-1], 1, start, end - 1, piles);
      }
    } else {
      // Bob's turn
      if (end - start == 1) {
        return !(net - piles[start] > 0);
      } else {
        // return !(!A || !B) -> return A && B
        return stoneGame(net - piles[start], 0, start + 1, end, piles)
            && stoneGame(net - piles[end-1], 0, start, end - 1, piles);
      }
    }
  }
};

int main() {
  Solution demo;
  vector<int> pile{3,7,2,3};
  std::cout << demo.stoneGame(pile) << "\n";
}
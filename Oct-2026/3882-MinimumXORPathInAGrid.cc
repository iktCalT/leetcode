#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        // bfs + dp
        // 0 <= grid[i][j] <= 1023​ -> 0 <= dp[i][j][x] <= 1023
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<vector<bool>>> dp (m, vector<vector<bool>>(n, vector<bool>(1024, false)));

        dp[0][0][grid[0][0]] = true;

        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < 1024; ++k) {
                if (dp[0][j-1][k])
                    dp[0][j][grid[0][j] ^ k] = true;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int k = 0; k < 1024; ++k) {
                if (dp[i-1][0][k])
                    dp[i][0][grid[i][0] ^ k] = true;
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                int cur = grid[i][j];
                for (int k = 0; k < 1024; ++k) {
                    if (dp[i-1][j][k])
                        dp[i][j][cur ^ k] = true;
                }
                for (int k = 0; k < 1024; ++k) {
                    if (dp[i][j-1][k])
                        dp[i][j][cur ^ k] = true;
                }
            }
        }

        for (int k = 0; k < 1024; ++k) {
            if (dp[m-1][n-1][k])
                return k;
        }
        return 0; // 0 xor a = a
    }
};

// TLE, but much faster than Solution0
class Solution1 {
public:
    int minCost(vector<vector<int>>& grid) {
        // bfs + dp
        // 0 <= grid[i][j] <= 1023​ -> 0 <= dp[i][j][x] <= 1023
        int m = grid.size();
        int n = grid[0].size();
        int k = 1024;
        vector<vector<unordered_set<int>>> dp (m, vector<unordered_set<int>>(n));
        dp[0][0].emplace(grid[0][0]);

        for (int j = 1; j < n; ++j) {
            dp[0][j].emplace(grid[0][j] ^ *dp[0][j-1].begin());
        }
        for (int i = 1; i < m; ++i) {
            dp[i][0].emplace(grid[i][0] ^ *dp[i-1][0].begin());
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                for (int prev : dp[i-1][j]) {
                    dp[i][j].emplace(grid[i][j] ^ prev);
                }
                for (int prev : dp[i][j-1]) {
                    dp[i][j].emplace(grid[i][j] ^ prev);
                }
            }
        }

        int min_cost = INT_MAX;
        for (int cost : dp[m-1][n-1]) min_cost = min(min_cost, cost);
        return min_cost; // 0 xor a = a
    }
};

// TLE
class Solution0 {
public:
    int minCost(vector<vector<int>>& grid) {
        // dfs
        m = grid.size();
        n = grid[0].size();

        return dfs(0, 0, 0, grid); // 0 xor a = a
    }

private:
    int m=0, n=0;
    int dfs(int current, int i, int j, vector<vector<int>>& grid) {
        current = current ^ grid[i][j];
        if (i == m-1 && j == n-1) {
            return current;
        } else if (i == m-1) {
            return dfs(current, i, j+1, grid);
        } else if (j == n-1) {
            return dfs(current, i+1, j, grid);
        } else {
            return min(dfs(current, i, j+1, grid),
                    dfs(current, i+1, j, grid));
        }
    }
};
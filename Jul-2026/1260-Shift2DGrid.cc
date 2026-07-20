#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int m = grid.size();
    int n = grid[0].size();
    k = k % (m * n);

    vector<vector<int>> ans(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        // old index
        int idx = i * n + j;
        // new index
        idx = (idx + k) % (m * n);
        ans[idx / n][idx % n] = grid[i][j];
      }
    }
    return ans;
  }
};
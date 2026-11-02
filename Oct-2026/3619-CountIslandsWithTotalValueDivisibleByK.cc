#include <vector>
using namespace std;

class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();
        this->k = k;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));

        int count = 0;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 0 && !visited[i][j]) {
                    count += dfs(i, j, grid) % k == 0;
                }
            }
        }
        return count;
    }
private:
    int m, n, k;
    vector<vector<bool>> visited;

    int dfs(int i, int j, vector<vector<int>>& grid) {
        // return the sum of island
        if (i < 0 || i >= m || j < 0 || j >= n
            || grid[i][j] == 0
            || visited[i][j]) return 0;

        visited[i][j] = true;
        return grid[i][j]
            + dfs(i-1, j, grid) % k
            + dfs(i+1, j, grid) % k
            + dfs(i, j-1, grid) % k
            + dfs(i, j+1, grid) % k;
    }
};
#include <queue>
#include <vector>
using namespace std;

// 6ms
class Solution {
public:
  int closedIsland(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    visited = vector<vector<bool>>(m, vector<bool>(n, false));
    // bfs
    int island = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        island += bfs(i, j, grid);
      }
    }
    return island;
  }

private:
  vector<vector<bool>> visited;

  struct Point {
    int x;
    int y;
  };

  bool bfs(int i, int j, vector<vector<int>> &grid) {
    if (visited[i][j] || grid[i][j] != 0)
      return false;

    bool is_island = true;
    int m = grid.size();
    int n = grid[0].size();

    queue<Point> que;
    que.push({i, j});
    while (!que.empty()) {
      Point p = que.front();
      que.pop();
      if (p.x < 0 || p.x >= m || p.y < 0 || p.y >= n || visited[p.x][p.y] ||
          grid[p.x][p.y] != 0) {
        continue;
      }
      visited[p.x][p.y] = true;
      if (p.x == 0 || p.x == m - 1 || p.y == 0 || p.y == n - 1)
        is_island = false;
      que.push({p.x - 1, p.y});
      que.push({p.x + 1, p.y});
      que.push({p.x, p.y - 1});
      que.push({p.x, p.y + 1});
    }
    return is_island;
  }
};

// 16ms
class Solution0 {
public:
  int closedIsland(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    visited = vector<vector<bool>>(m, vector<bool>(n, false));
    // bfs
    int island = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        island += bfs(i, j, grid);
      }
    }
    return island;
  }

private:
  vector<vector<bool>> visited;

  struct Point {
    int x;
    int y;
  };

  bool bfs(int i, int j, vector<vector<int>> &grid) {
    if (visited[i][j] || grid[i][j] != 0)
      return false;

    bool is_island = true;
    int m = grid.size();
    int n = grid[0].size();

    queue<Point> que;
    que.push({i, j});
    while (!que.empty()) {
      Point p = que.front();
      que.pop();
      if (grid[p.x][p.y] != 0) {
        continue;
      }
      visited[p.x][p.y] = true;
      if (p.x == 0 || p.x == m - 1 || p.y == 0 || p.y == n - 1)
        is_island = false;
      if (p.x - 1 >= 0 && !visited[p.x - 1][p.y])
        que.push({p.x - 1, p.y});
      if (p.x + 1 < m && !visited[p.x + 1][p.y])
        que.push({p.x + 1, p.y});
      if (p.y - 1 >= 0 && !visited[p.x][p.y - 1])
        que.push({p.x, p.y - 1});
      if (p.y + 1 < n && !visited[p.x][p.y + 1])
        que.push({p.x, p.y + 1});
    }
    return is_island;
  }
};
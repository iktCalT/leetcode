#include <array>
#include <deque>
#include <vector>

using namespace std;

struct Cell {
  int r;
  int c;
};

const array<Cell, 4> directions = {
  Cell{-1, 0}, 
  Cell{0, -1}, 
  Cell{1, 0}, 
  Cell{0, 1}
};

class Solution {
public:
  bool findSafeWalk(vector<vector<int>>& grid, int health) {
    // Use a 2D grid (we can use the original grid), recording 
    // the mim possible hurt from 0,0 to here
    // For each cell, modify its adjacent 4 cells, once a cell is 
    // modified, add it to queue 
    // If a cell is re-modified, cut in line! Otherwise, we have to
    // re-modify many cells
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> min_hurt(m, vector<int>(n, INT_MAX));
    deque<Cell> que;

    min_hurt[0][0] = grid[0][0];
    que.emplace_back(0, 0);
    while (!que.empty()) {
      explore(que, min_hurt, grid);
    }
    return health > min_hurt[m - 1][n - 1];
  }

private:
  void explore(deque<Cell>& que, vector<vector<int>>& min_hurt,
      const vector<vector<int>>& grid) {
    Cell cur = que.front();
    que.pop_front();
    int& r = cur.r;
    int& c = cur.c;

    for (const Cell dir : directions) {
      // new r and new c
      int nr = r + dir.r;
      int nc = c + dir.c;
      if (nr >= 0 && nc >= 0 && nr < grid.size() && nc < grid[0].size()) {
        int nh = min_hurt[r][c] + grid[nr][nc]; // new hurt
        if (nh >= min_hurt[nr][nc]) continue;
        // if nh < min_hurt[nr][nc];
        min_hurt[nr][nc] == INT_MAX 
          ? que.emplace_back(nr, nc)
          : que.emplace_front(nr, nc);
        min_hurt[nr][nc] = nh;
      }
    }
  }
};
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    // BFS: if visited, change to '0'
    int cnt = 0;
    for (int r = 0; r < grid.size(); ++r) {
      for (int c = 0; c < grid[0].size(); ++c) {
        if (grid[r][c] == '1') {
          BFS(r, c, grid);
          ++cnt;
        }
      }
    }
    return cnt;
  }

private:
  inline void changeDir(pair<int, int>& dir) {
    // right: 0,1; down: 1, 0; left: 0, -1; up: -1, 0
    // x = y; y = -x
    int y = dir.second;
    dir.second = -dir.first; // y = -x
    dir.first = y; // x = y
  }

  void BFS(int r, int c, vector<vector<char>>& grid) {
    grid[r][c] = '0';
    queue<pair<int, int>> que;
    // row = row + dir.first; col = col + dir.second
    pair<int, int> dir = {0, 1}; // go right
    que.push({r, c});
    while (!que.empty()) {
      auto pos = que.front();
      r = pos.first;
      c = pos.second;
      que.pop();
      for (int _ = 0; _ < 4; ++_) {
        int nr = r + dir.first;
        int nc = c + dir.second;
        if (!(nr < 0 || nr >= grid.size() 
            || nc < 0 || nc >= grid[0].size() 
            || grid[nr][nc] == '0')) {
          que.push({nr, nc});
          grid[nr][nc] = '0'; // set as visited
        }
        changeDir(dir);
      }
    }
  }
};

int main() {
  Solution demo;
  vector<vector<char>> grid{{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
  std::cout << demo.numIslands(grid) << "\n";
}
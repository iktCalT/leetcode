#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  int minMoves(vector<string>& classroom, const int max_energy) {
    // There are at most 10 'L' cells in the grid.
    // -> We can use int or uint16_t to represent mask
    int m = classroom.size();     // 1 <= m <= 20
    int n = classroom[0].size();  // 1 <= n <= 20
    auto [k, init_status] = goThrough(classroom, max_energy); // 0 <= k <= 10
    if (k == 0) return 0;
    const int full_mask = (1 << k) - 1;

    vector<vector<vector<int>>> best_energy(m, 
            vector<vector<int>>(n, 
            vector<int>(2 << k, 
            -1)));
    best_energy[init_status.x][init_status.y][0] = max_energy;

    queue<Status> que;
    que.push(init_status);
    int ans = INT_MAX;

    while (!que.empty()) {
      Status s = que.front(); // s: status
      que.pop();

      Dir dir = {1, 0};
      for (int _ = 0; _ < 4; ++_, dir.next()) {
        newStatus(s, dir, classroom, best_energy, max_energy, que, ans, full_mask); // ns: new status
      }
    }

    if (ans == INT_MAX) return -1;
    return ans;
  }

private:
  struct Status {
    int x;
    int y;
    int mask;
    int energy;
    int steps;
  };

  struct Dir {
    int x;
    int y;

    void next() { // become {-y, x} 
      int tmp = y;
      y = x;
      x = -tmp;
    }
  };

  tuple<int, Status> goThrough(vector<string>& classroom, const int max_energy) {
    int m = classroom.size();    
    int n = classroom[0].size(); 
    int count = 0;
    int sx = 0;
    int sy = 0;
    int label = '0';
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (classroom[i][j] == 'L') {
          ++count;
          classroom[i][j] = label; // label litters from '0' to '9' (at most 10 litters)
          ++label;
        } else if (classroom[i][j] == 'S') {
          sx = i;
          sy = j;
        }
      }
    }
    return {count, Status{sx, sy, 0, max_energy, 0}};
  }

  void newStatus(
      const Status& s, 
      const Dir dir,
      const vector<string>& classroom, 
      vector<vector<vector<int>>>& best_energy,
      const int max_energy,
      queue<Status>& que,
      int& ans,
      const int full_mask) {
    int m = classroom.size();
    int n = classroom[0].size();
    int mask = s.mask;
    int energy = s.energy;
    int nx = s.x + dir.x;
    int ny = s.y + dir.y;
    int nsteps = s.steps + 1;
    if (nx < 0 || nx >= m || ny < 0 || ny >= n || energy == 0) return;

    switch (classroom[nx][ny]) {
    case 'X':
      return;
    case 'R':
      energy = max_energy;
      break;
    case 'S':
    case '.':
      energy -= 1;
      break;
    default: // litters from '0' to '9'
      energy -= 1;
      mask = mask | (1 << (classroom[nx][ny] - '0'));
      if (mask == full_mask) ans = min(nsteps, ans);
    }

    if (energy > best_energy[nx][ny][mask]) {
      best_energy[nx][ny][mask] = energy;
      que.push({nx, ny, mask, energy, nsteps});
    }
  }
};

int main() {
  Solution demo;
  vector<string> classroom {"S.", "XL"};
  std::cout << demo.minMoves(classroom, 2) << "\n";
}
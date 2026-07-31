#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

using namespace std;

/* Modified from other's answer */
class Solution {
public:
  int countLessEqual(vector<vector<int>> &matrix, int mid) {
    // How many elements <= mid
    int n = matrix.size();

    int count = 0;
    int col = 0;
    for (int row = n - 1; row >= 0; --row) {
      auto it = -1 + upper_bound(matrix[row].begin() + col, matrix[row].end(), mid);
      col = distance(matrix[row].begin(), it);
      count += col + 1;
      col = max(col, 0);
    }

    return count;
  }

  int kthSmallest(vector<vector<int>> &matrix, int k) {
    int n = matrix.size();

    int low = matrix[0][0];
    int high = matrix[n - 1][n - 1];

    while (low < high) {
      int mid = low + (high - low) / 2;

      if (countLessEqual(matrix, mid) < k) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    return low;
  }
};

class Solution1 { // 7ms
public:
  int kthSmallest(vector<vector<int>> &matrix, int k) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> prev_frontier(m, -1); // frontiers of each row
    vector<int> frontier(m, -1);
    int prev_smaller = 0;
    int smaller = 0;

    int i = 0;
    while (true) {
      addFrontier(i, prev_frontier, frontier, matrix);
      smaller = countFrontier(frontier);
      if (smaller < k) {
        prev_smaller = smaller;
        prev_frontier = frontier;
        if (i != n - 1)
          ++i;
      } else {
        if (smaller == k || smaller - prev_smaller == 1) // including i == 0
          return matrix[i][prev_frontier[i] + 1];
        frontier = prev_frontier;
        --i;
      }
    }
  }

private:
  inline int countFrontier(const vector<int> &frontier) {
    int n = frontier.size();
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      cnt += frontier[i] + 1;
    }
    return cnt;
  }

  void addFrontier(int row, const vector<int> &prev_frontier,
                   vector<int> &frontier, const vector<vector<int>> &matrix) {
    if (prev_frontier[row] == matrix[0].size() - 1) {
      frontier[row + 1] += 1;
      return;
    }

    int val = matrix[row][prev_frontier[row] + 1];
    for (int i = 0; i < row; ++i) {
      auto it = upper_bound(matrix[i].begin(), matrix[i].end(), val);
      frontier[i] = distance(matrix[i].begin(), it) - 1;
    }
    frontier[row] += 1;
  }
};

struct Cor {
  int val;
  int r;
  int c;
};

class Solution0 { // 11ms
public:
  int kthSmallest(vector<vector<int>> &matrix, int k) {
    // Heap
    int n = matrix.size();
    priority_queue<Cor, vector<Cor>,
                   decltype([](const Cor &lhs, const Cor &rhs) {
                     return lhs.val > rhs.val;
                   })>
        frontier;
    frontier.push({matrix[0][0], 0, 0});

    while (!frontier.empty()) {
      Cor cur = frontier.top();
      frontier.pop();
      --k;
      if (k == 0)
        return cur.val;

      int nr = cur.r, nc = cur.c + 1;
      if (nr < n && nc < n && matrix[nr][nc] != INT_MIN) {
        frontier.push({matrix[nr][nc], nr, nc});
        matrix[nr][nc] = INT_MIN; // mark as visited
      }
      nr = cur.r + 1, nc = cur.c;
      if (nr < n && nc < n && matrix[nr][nc] != INT_MIN) {
        frontier.push({matrix[nr][nc], nr, nc});
        matrix[nr][nc] = INT_MIN;
      }
    }

    return 0; // should not happen
  }
};

int main() {
  Solution demo;
  vector<vector<int>> m{{1, 4, 7, 11, 15},
                        {2, 5, 8, 12, 19},
                        {3, 6, 9, 16, 22},
                        {10, 13, 14, 17, 24},
                        {18, 21, 23, 26, 30}};
  std::cout << demo.kthSmallest(m, 20) << "\n";
}
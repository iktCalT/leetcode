#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cor {
  int val;
  int r;
  int c;
};

class Solution {
public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    // Heap
    int n = matrix.size();
    priority_queue<Cor, vector<Cor>, 
    decltype([](const Cor& lhs, const Cor& rhs){return lhs.val > rhs.val;})> frontier;
    frontier.push({matrix[0][0], 0, 0});

    while (!frontier.empty()) {
      Cor cur = frontier.top();
      frontier.pop();
      --k;
      if (k == 0) return cur.val;
      
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
  vector<vector<int>> m{ {1,5,9 }, {10,11,13 }, {12,13,15 }};
  std::cout << demo.kthSmallest(m, 8) << "\n";
}
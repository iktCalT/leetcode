#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int findCircleNum(vector<vector<int>>& isConnected) {
    unordered_set<int> visited;
    visited.reserve(isConnected.size());

    int ans = 0;
    for (int i = 0; i < isConnected.size(); ++i) {
      if (visited.contains(i)) continue;
      visited.insert(i);
      dfs(i, visited, isConnected);
      ++ans;
    }

    return ans;
  }

private:
  void dfs(int i, unordered_set<int>& visited, 
          const vector<vector<int>>& isConnected) {
    for (int j = 0; j < isConnected.size(); ++j) {
      if (!isConnected[i][j] || visited.contains(j))  continue;
      
      visited.insert(j);
      dfs(j, visited, isConnected);
    } 
  }
};

int main() {
  Solution demo;
  vector<vector<int>> con{{1,1,0},{1,1,0},{0,0,1}};
  std::cout << demo.findCircleNum(con) << "\n";
}
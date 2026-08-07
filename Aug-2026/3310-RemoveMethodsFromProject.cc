#include <deque>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/* 189 ms */
class Solution {
private:
  struct Node {
    vector<int> next;
    bool suspicious = false;
  };

public:
  vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
    vector<Node> invocations_map(n);

    for (const auto& i : invocations) {
      invocations_map[i[0]].next.push_back(i[1]);
    }

    // BFS, find all suspicious
    deque<int> que;
    que.push_back(k);

    while (!que.empty()) {
      int current = que.front();
      que.pop_front();
      if (invocations_map[current].suspicious == true) continue;
      
      invocations_map[current].suspicious = true;
      que.insert(que.end(), invocations_map[current].next.begin(), invocations_map[current].next.end());
    }

    vector<int> ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (invocations_map[i].suspicious) continue;

      ans.push_back(i);
      for (int next : invocations_map[i].next) {
        if (invocations_map[next].suspicious) {
          // return all
          vector<int> all;
          all.reserve(n);
          for (int j = 0; j < n; ++j) {
            all.push_back(j);
          }
          return all;
        }
      }
    }
    return ans;
  }
};

/* 412 ms */
class Solution0 {
public:
  vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
    unordered_map<int, vector<int>> invocations_map;
    for (int i = 0; i < n; ++i) {
      invocations_map.emplace(i, vector<int>());
    }

    for (const auto& i : invocations) {
      invocations_map[i[0]].push_back(i[1]);
    }

    // BFS, find all suspicious
    unordered_set<int> suspicious;
    queue<int> que;
    que.push(k);

    while (!que.empty()) {
      int i = que.front();
      que.pop();
      // if (suspicious.contains(i)) continue;

      suspicious.insert(i);
      for (int& j : invocations_map[i]) {
        if (!suspicious.contains(j)) que.push(j);
      }
    }

    vector<int> not_suspicious;
    not_suspicious.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (suspicious.contains(i)) continue;
      not_suspicious.push_back(i);

      for (int invocated : invocations_map[i]) {
        if (suspicious.contains(invocated)) { // return all methods
          vector<int> all;
          all.reserve(n);
          for (int j = 0; j < n; ++j) {
            all.push_back(j);
          }
          return all;
        }
      }
    }
    return not_suspicious;
  }
};
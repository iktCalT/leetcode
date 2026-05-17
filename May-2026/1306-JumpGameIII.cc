#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  bool canReach(vector<int> &arr, int start) {
    // DFS
    // arr[start] < 0 means "reached"
    if (start < 0 || start >= arr.size() || arr[start] < 0)
      return false;

    if (arr[start] == 0)
      return true;
    int current = arr[start];
    arr[start] = -1; // mark this position as "reached" before calling

    if (canReach(arr, start + current))
      return true;
    if (canReach(arr, start - current))
      return true;

    return false;
  }

  bool canReachBFS(vector<int>& arr, int start) {
      // BFS
      queue<int> que;
      vector<bool> isinque(arr.size(), false);

      que.push(start);
      isinque[start] = true;
      while (!que.empty()) {
          int cur = que.front();
          que.pop();

          if (arr[cur] == 0) return true;
          if (cur + arr[cur] < arr.size() && !isinque[cur + arr[cur]]) {
              que.push(cur + arr[cur]);
              isinque[cur + arr[cur]] = true;
          }
          if (cur - arr[cur] >= 0 && !isinque[cur - arr[cur]]) {
              que.push(cur - arr[cur]);
              isinque[cur - arr[cur]] = true;
          }
      }

      return false;
  }
};
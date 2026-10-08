#include <vector>
using namespace std;

class Solution {
public:
  vector<int> maxDepthAfterSplit(string seq) {
    int n = seq.size();
    vector<int> dep(n, 0);
    vector<int> ans(n);
    // seq is VPS
    for (int i = 1; i < n - 1; ++i) {
      if (seq[i] == '(') {
        dep[i] = dep[i - 1] + dep[i] + 1;
      } else {
        dep[i] = dep[i - 1] + dep[i];
        dep[i + 1] = - 1; // i <= n - 2
      }
      ans[i] = dep[i] % 2;
    }

    // dep[0] = dep[n - 1] = 0
    ans[0] = 0;
    ans[n-1] = 0;
    return ans;
  }
};

class Solution_0 {
public:
  vector<int> maxDepthAfterSplit(string seq) {
    int n = seq.size();
    vector<int> dep(n, 0);
    int max_dep = 0;
    // seq is VPS
    for (int i = 1; i < n - 1; ++i) {
      if (seq[i] == '(') {
        dep[i] = dep[i - 1] + dep[i] + 1;
        max_dep = max(max_dep, dep[i]); // i >= 1
      } else {
        dep[i] = dep[i - 1] + dep[i];
        dep[i + 1] = - 1; // i <= n - 2
      }
    }

    for (auto it = dep.begin(); it != dep.end(); ++it) {
      *it = *it <= max_dep / 2 ? 0 : 1;
    }
    return dep;
  }
};
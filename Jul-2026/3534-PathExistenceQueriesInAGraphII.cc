#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> pathExistenceQueries(int n, vector<int> &nums, int maxDiff,
                                   vector<vector<int>> &queries) {
    // Greedy
    vector<int> pos = nums;
    sort(pos.begin(), pos.end());
    // parent (1st ancestor): the furthest position it can go to within 1 jump
    // 'ancestors' stores 1st, 2nd, 4th, 8th, 16th ancestors
    vector<vector<int>> ancestors(n);
    for (int i = 0; i < n; ++i)
      ancestors[i].reserve(log(n));

    // Fill in parents (-1 if no parent)
    for (int i = 0; i < n; ++i) {
      int prt = findSmaller(pos[i] + maxDiff, i, pos);
      if (prt != i)
        ancestors[i].push_back(prt);
    }

    for (int i = n - 1; i >= 0; --i) {
      vector<int> &cld = ancestors[i];
      if (cld.empty())
        continue; // no parent

      int pow = 0;
      while (pow < ancestors[cld[pow]].size()) {
        cld.push_back(ancestors[cld[pow]][pow]);
        ++pow;
      }
    }

    int m = queries.size();
    vector<int> ans(m);

    for (int i = 0; i < m; ++i) {
      const vector<int> &query = queries[i];
      if (query[0] == query[1]) {
        ans[i] = 0;
        continue;
      }

      // Convert from positions to indices
      int start = findSmaller(min(nums[query[0]], nums[query[1]]), 0, pos);
      int end = findSmaller(max(nums[query[0]], nums[query[1]]), 0, pos);

      int jumps = start == end;
      while (!ancestors[start].empty() && start != end && ancestors[start][0] < end) {
        int power = findSmaller(end, 0, ancestors[start]);
        jumps += 1 << power; // jump 2 ^ power steps
        start = ancestors[start][power];
      }

      if (start == end) {
        ans[i] = jumps;
      } else if (!ancestors[start].empty() && ancestors[start][0] >= end) {
        ans[i] = jumps + 1;
      } else  {
        ans[i] = -1;
      }
    }
    return ans;
  }

private:
  int findSmaller(int val, int start, const vector<int> &vec) {
    // Find the index of first element that is <= val
    // in a ascending vector.
    // start: starting index
    int end = vec.size();
    while (end - start > 1) {
      int mid = (start + end) / 2;
      if (vec[mid] == val) {
        return mid;
      } else if (vec[mid] < val) {
        start = mid;
      } else if (vec[mid] > val) {
        end = mid;
      }
    }
    return start;
  }
};

/* Time Limit Exceeded */
class Solution0 {
public:
  vector<int> pathExistenceQueries(int n, vector<int> &nums, int maxDiff,
                                   vector<vector<int>> &queries) {
    // Greedy
    map<int, int> nodemap; // key: position, value: furthest next position
    nodemap.insert({nums[0], nums[0]});

    for (int i = 1; i < n; ++i) {
      auto it = nodemap.insert({nums[i], nums[i]}).first;

      // Modify self next
      auto next_it = next(it);
      while (next_it != nodemap.end() &&
             (next_it->first - it->first) <= maxDiff)
        next_it = next(next_it);
      it->second = prev(next_it)->first;

      // Modify nexts of previous nodes
      auto prev_it = make_reverse_iterator(it);
      while (prev_it != nodemap.rend() &&
             (it->first - prev_it->first) <= maxDiff) {
        prev_it->second = max(prev_it->second, it->first);
        prev_it = next(prev_it);
      }
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (const vector<int> &query : queries) {
      if (query[0] == query[1]) {
        ans.push_back(0);
        continue;
      }

      int current = min(nums[query[0]], nums[query[1]]);
      int end = max(nums[query[0]], nums[query[1]]);

      int steps = 1;
      while (nodemap[current] < end) {
        ++steps;
        if (current == nodemap[current]) {
          steps = -1;
          break;
        } else {
          current = nodemap[current];
        }
      }
      ans.push_back(steps);
    }
    return ans;
  }
};

int main() {
  Solution demo;
  vector<int> nums{8, 4};
  vector<vector<int>> queries{{0, 1}, {1,0}};
  demo.pathExistenceQueries(nums.size(), nums, 2, queries);
}
#include <unordered_map>
#include <vector>
using namespace std;

// 194ms
class Solution {
public:
  int minimumDistance(vector<int>& nums) {
    // abs(i - j) + abs(j - k) + abs(k - i) 
    // = 2 * (max(i, j, k) - min(i, j, k))

    unordered_map<int, pair<int, int>> map;
    int n = nums.size();
    int min_dist = INT_MAX;
    for (int i = 0; i < n; ++i) {
      auto [it, success] = map.try_emplace(nums[i], i, -1);
      if (!success) {
        if (it->second.second == -1) {
          it->second.second = i;
        } else {
          auto [first, second] = it->second;
          min_dist = min(min_dist, i - first);

          it->second.first = second;
          it->second.second = i;
        }
      }
    }

    if (min_dist == INT_MAX) return -1;
    return 2 * min_dist;
  }
};

// 743ms
class Solution0 {
public:
  int minimumDistance(vector<int>& nums) {
    // abs(i - j) + abs(j - k) + abs(k - i) 
    // = 2 * (max(i, j, k) - min(i, j, k))

    unordered_map<int, vector<int>> map;
    for (auto cit = nums.cbegin(); cit != nums.cend(); ++cit) {
      int i = distance(nums.cbegin(), cit);
      auto[it, success] = map.try_emplace(*cit, vector<int>{i});
      if (!success) it->second.push_back(i);
    }

    int min_dist = INT_MAX;
    for (const auto [_, vec] : map) {
      min_dist = min(min_dist, min_good_dist(vec));
      if (min_dist == 2) break;
    }
    if (min_dist == INT_MAX) return -1;
    return 2 * min_dist;
  }

private:
  int min_good_dist(const vector<int> &vec) {
    int n = vec.size();

    int min_dist = INT_MAX;
    for (int i = 0; i < n-2; ++i) {
      min_dist = min(min_dist, vec[i+2] - vec[i]);
    }
    return min_dist;
  }
};
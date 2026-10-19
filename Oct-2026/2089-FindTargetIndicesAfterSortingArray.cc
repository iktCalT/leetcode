#include <algorithm>
#include <vector>
using namespace std;

// 0ms, O(n)
class Solution {
public:
  vector<int> targetIndices(vector<int>& nums, int target) {
    int smaller_cnt = 0;
    int equal_cnt = 0;
    for (const int n : nums) {
      if (n < target) {
        ++smaller_cnt;
      } else if (n == target) {
        ++equal_cnt;
      }
    }
    vector<int> indices(equal_cnt);
    for (int i = 0; i < equal_cnt; ++i) {
      indices[i] = smaller_cnt + i;
    }

    return indices;
  }
};

// 1ms, straight forward, O(nlgn)
class Solution0 {
public:
  vector<int> targetIndices(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<int> indices = {};
    for (int i = 0; i < n; ++i) {
      if (nums[i] == target) {
        indices.push_back(i);
      }
    }
    return indices;
  }
};
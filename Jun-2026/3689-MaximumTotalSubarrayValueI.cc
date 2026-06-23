#include <array>
#include <vector>

using namespace std;

class Solution { // 0ms
public:
  long long maxTotalValue(vector<int>& nums, int k) {
    // 0 <= nums[i] <= 10^9, 1 <= k <= 10^5
    // nums[i] * k could be greater than INT_MAX, so, use long long
    array<long long, 3> minmax{nums[0], 0, nums[0]};
    for (int i = 1; i < nums.size(); ++i) {
      // if nums[i] > max, then don't need to modify min
      int pos = nums[i] > minmax[0] 
                ? nums[i] > minmax[2] 
                ? 2 
                : 1 
                : 0;
      minmax[pos] = nums[i];
    }
    return (minmax[2] - minmax[0]) * k;
  }
};

class Solution0 { // 1ms
public:
  long long maxTotalValue(vector<int>& nums, int k) {
    // 0 <= nums[i] <= 10^9, 1 <= k <= 10^5
    // nums[i] * k could be greater than INT_MAX, so, use long long
    long long max_n = nums[0];
    long long min_n = nums[0];
    for (long long num : nums) {
      max_n = max(max_n, num);
      min_n = min(min_n, num);
    }
    return (max_n - min_n) * k;
  }
};
#include <vector>
using namespace std;

class Solution {
public:
  int sortPermutation(vector<int>& nums) {
    int ans = -1; // 1111...1111
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i) {
        ans &= nums[i];
      }
    }
    return max(ans, 0);
  }
};
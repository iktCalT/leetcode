#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> leftRightDifference(vector<int>& nums) {
    // leftSum[k+1] = leftSum[k] + nums[k]
    // rightSum[k+1] = rightSum[k] - nums[k+1]
    int diff = 0; 
      // don't change ans directly, 
      // in case nums[i] < 0 (although 
      // this problem constraints this)
    for (int i = 1; i < nums.size(); ++i) {
      diff -= nums[i];
    }
    
    vector<int> ans(nums.size());
    ans[0] = abs(diff);
    for (int i = 1; i < nums.size(); ++i) {
      diff += nums[i - 1] + nums[i];
      ans[i] = abs(diff);
    }
    return ans;
  }
};
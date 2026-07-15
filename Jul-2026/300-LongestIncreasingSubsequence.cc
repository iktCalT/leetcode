#include <vector>
using namespace std;

class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    // dp[5] = 8 means that there is a increasing subsequence,
    // whose size is 5, and whose last value is 8
    vector<int> dp = {INT_MIN};
    for (int num : nums) {
      // dp[0] to dp[dp.size() - 2]
      for (int i = 0; i + 1 < dp.size(); ++i) {
        if (dp[i] < num)
          dp[i + 1] = min(dp[i + 1], num);
      }

      // dp[dp.size() - 1]
      if (dp.back() < num)
        dp.push_back(num);
    }
    return dp.size() - 1; // delete leading INT_MIN
  }
};
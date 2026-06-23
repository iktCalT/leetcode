#include <vector>

using namespace std;

class Solution {
public:
  vector<int> resultsArray(vector<int>& nums, int k) {
    int cnt_dwn;
    vector<int> ans(nums.size() - k + 1, -1);
    for (int i = 0; i < nums.size(); ++i) {
      if (i != 0 && nums[i] == nums[i - 1] + 1) {
        --cnt_dwn;
      } else { // i == 0 || nums[i] != nums[i - 1] + 1
        cnt_dwn = k - 1;
      }

      if (cnt_dwn == 0) {
        ans[i - k + 1] = nums[i];
        cnt_dwn = 1;
      }
    }
    return ans;
  }
};
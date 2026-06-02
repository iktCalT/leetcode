class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    if (nums.size() <= 1) return nums.size();
    sort(nums.begin(), nums.end());
    int ans = 1;
    int cnt = 1;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1] + 1) {
        ++cnt;
        ans = max(ans, cnt);
      } else if (nums[i] == nums[i - 1]) {
        // do nothing 
      } else {
        cnt = 1;
      }
    }
    
    return ans;
  }
};
#include <vector>
using namespace std;

class Solution {
public:
  int largestInteger(vector<int>& nums, int k) {
    // k <= nums.length
    
    // Assume all elements in nums appear exactly once
    // If k == 1, return max(nums)
    // If k == nums.size(), return max(nums)
    // If 2 < k < nums.size(), return max(nums.front(), nums.back())

    int n = nums.size();
    if (k == 1) {
      return all(nums);
    } else if (k == n) {
      return max_(nums);
    } else {
      return twoEnds(nums);
    }
  }

private:
  int all(vector<int>& nums) {
    // Notice 0 <= nums[i] <= 50
    int n = nums.size();
    array<int, 51> cnt;
    for (int i = 0; i < n; ++i) {
      ++cnt[nums[i]];
    }

    for (int i = 50; i >= 0; --i) {
      if (cnt[i] == 1) return i;
    }
    return -1;
  }

  int max_(vector<int>& nums) {
    int ans = INT_MIN;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      ans = max(ans, nums[i]);
    }
    return ans;
  }

  int twoEnds(vector<int>& nums) {
    int n = nums.size();
    int front = nums.front();
    int back = nums.back();
    bool isFront = true;
    bool isBack = true;
    if (front == back) return -1;

    for (int i = 1; i < n - 1; ++i) {
      isFront = nums[i] == front ? false : isFront;
      isBack = nums[i] == back ? false : isBack;
    }

    if (isFront && isBack) {
      return max(front, back);
    } else if (isFront) {
      return front;
    } else if (isBack) {
      return back;
    } else {
      return -1;
    }
  }
};
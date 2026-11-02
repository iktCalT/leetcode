#include <algorithm>
#include <vector>

using namespace std;

// 52ms
class Solution {
public:
  long long maxAlternatingSum(vector<int>& nums) {
    for (int& n : nums) {
      n = abs(n);
    }

    sort(nums.begin(), nums.end(), greater<int>());
    int n = nums.size();
    long long ans = 0;
    for (int i = 0; i < n/2; ++i) {
      ans += nums[i] * nums[i];
      ans -= nums[n - 1 - i] * nums[n - 1 - i];
    }
    if (n % 2) {ans += nums[(n-1)/2] * nums[(n-1)/2];}

    return ans;
  }
};

// 63ms
class Solution0 {
public:
  long long maxAlternatingSum(vector<int>& nums) {
    sort(nums.begin(), nums.end(), [](int& a, int& b) {return abs(a) > abs(b);});
    int n = nums.size();
    long long ans = 0;
    for (int i = 0; i < (n+1)/2; ++i) {
      ans += nums[i] * nums[i];
    }

    for (int i = (n+1)/2; i < n; ++i ){
      ans -= nums[i] * nums[i];
    }
    return ans;
  }
};
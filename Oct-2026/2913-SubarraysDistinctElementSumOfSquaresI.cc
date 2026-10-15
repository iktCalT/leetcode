#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 36ms
class Solution {
public:
  int sumCounts(vector<int>& nums) {
    // Brute force 2
    const int n = nums.size(); // all single element subarrays
    int ans = n;
    for (int i = 0; i < n; ++i) {
      unordered_set<int> dist {nums[i]};
      for (int j = i + 1; j < n; ++j) { 
        // start: i; end: j; length: start from 2
        dist.insert(nums[j]);
        ans += dist.size() * dist.size();
      }
    }
    return ans;
  }
};

// 70ms
class Solution0 {
public:
  int sumCounts(vector<int>& nums) {
    // Brute force
    const int n = nums.size(); // all single element subarrays
    int ans = n;
    for (int len = 2; len <= n; ++len) {
      unordered_map<int, int> dist;
      for (int i = 0; i < len; ++i) {
        dist[nums[i]] += 1;
      }
      ans += dist.size() * dist.size();

      for (int j = 0; j + len < n; ++j) {
        dist[nums[j+len]] += 1;
        dist[nums[j]] -= 1;
        if (dist[nums[j]] == 0) {dist.erase(nums[j]);}
        ans += dist.size() * dist.size();
      }
    }
    return ans;
  }
};
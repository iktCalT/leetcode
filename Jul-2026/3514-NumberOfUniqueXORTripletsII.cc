#include <unordered_set>
#include <vector>
using namespace std;

/* Runtime 1989 ms Beats 42.13% */
class Solution {
public:
  int uniqueXorTriplets(vector<int>& nums) {
    // Brute force, 1 <= nums.length <= 1500
    unordered_set<int> first;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int tmp = nums[i];
      // don't need j == i, because it nums[i] ^ nums[i] == 0
      // and 0 ^ nums[k] == nums[k]. I will add nums[k] to ans
      // directly
      for (int j = 0; j < i; ++j) { 
        first.insert(nums[j] ^ tmp);
      }
    }

    // add nums[k] to ans directly
    unordered_set<int> ans (nums.begin(), nums.end());
    for (int tmp : first) 
      for (int k = 0; k < n; ++k)
        ans.insert(tmp ^ nums[k]);
    
    return ans.size();
  }
};
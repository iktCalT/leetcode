#include <vector>

using namespace std;

class Solution {
public:
  vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
    // Since nums is in non-descending order
    // If i and i + 1 are disconnected, then 
    // for any j <= i, k >= i + 1, j and k
    // are disconnected

    int group = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] - nums[i - 1] <= maxDiff) {
        nums[i - 1] = group;
      } else {
        nums[i - 1] = group;
        ++group;
      }
    }
    nums[nums.size() - 1] = group;

    vector<bool> ans(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      if (nums[queries[i][0]] == nums[queries[i][1]]) 
        ans[i] = true;
      else
        ans[i] = false;
    }
    return ans;
  }
};
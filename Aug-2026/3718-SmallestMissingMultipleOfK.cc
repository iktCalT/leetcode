#include <vector>
using namespace std;

class Solution {
public:
  int missingMultiple(vector<int>& nums, int k) {
    int n = nums.size();
    vector<bool> exist(n, false);

    for (int num : nums) {
      int mul = num / k;
      if (num == mul * k && mul <= n) exist[mul - 1] = true;
    }

    for (int i = 0; i < n; ++i) {
      if (exist[i] == false) return (i + 1) * k;
    }

    return (n + 1) * k;
  }
};
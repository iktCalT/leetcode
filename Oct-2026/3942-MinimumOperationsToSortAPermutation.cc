#include <vector>
using namespace std;

class Solution {
public:
  int minOperations(vector<int>& nums) {
    // It must be a rotated array of 0 to n-1 or n-1 to 0
    int n = nums.size();
    if (n == 1) return nums[0] == 0 - 1;

    int dir;
    if (((nums[1] - nums[0] + n) % n) == 1) {
      dir = 1;
    } else {
      dir = -1;
    }

    int index = 0;
    for (int i = 1; i < n; ++i) {
      int diff = nums[i] - nums[i-1];
      if (diff == dir) {
        continue;
      }
      else if (diff == dir * (1-n)) {
        index = i;
      } else {
        return -1;
      }
    }
    
    if (dir == 1) {
      return min(index, 2 + n - index);
    } else {
      return min(index + 1, 1 + n - index);
    }
  }
};
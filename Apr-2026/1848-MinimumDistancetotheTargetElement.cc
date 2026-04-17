#include <cstdlib>
#include <vector>

class Solution {
public:
  int getMinDistance(std::vector<int> &nums, int target, int start) {
    // searching from start. dst: distance
    for (int dst = 0; start - dst >= 0 || start + dst < (int) nums.size(); dst++) {
      if (start - dst >= 0 && nums[start - dst] == target) {
        return dst;
      }
      if (start + dst < (int) nums.size() && nums[start + dst] == target) {
        return dst;
      }
    }
    return -1;
  }
};
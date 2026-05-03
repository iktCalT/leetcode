#include <vector>

class Solution {
public:
  int removeElement(std::vector<int> &nums, int val) {
    if (nums.size() == 0) {
      return 0;
    }

    // from end to the beginning
    int cur = nums.size() - 1, front = cur;
    for (; front >= 0; front--) {
      if (nums[front] == val) {
        nums[front] = nums[cur];
        cur--;
      }
    }
    return cur + 1;
  }
};
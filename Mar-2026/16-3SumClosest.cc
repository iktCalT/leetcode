#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

class Solution {
public:
  int threeSumClosest(std::vector<int> &nums, int target) {
    int closest = INT_MAX;
    if (nums.size() < 3) {
      return closest;
    }

    // Sort, O(nlogn)
    std::sort(nums.begin(), nums.end());

    // Find from two ends, O(n2)
    for (size_t first = 0; first < nums.size() - 2; first++) {
      if (first >= 1 && nums[first] == nums[first - 1]) {
        continue;
      }

      size_t second = first + 1;
      size_t third = nums.size() - 1;
      int diff;
      while (second < third) {
        diff = nums[first] + nums[second] + nums[third] - target;
        if (diff == 0) {
          closest = diff;
          break;
        } else if (diff > 0) {
          closest = std::abs(closest) > abs(diff) ? diff : closest;
          do {
            third--;
          } while (nums[third] == nums[third + 1] && second < third);
        } else {
          closest = std::abs(closest) > abs(diff) ? diff : closest;
          do {
            second++;
          } while (nums[second] == nums[second - 1] && second < third);
        }
      }
    }
    return target + closest;
  }
};

int main() {
  Solution demo = Solution();
  std::vector<int> nums = {-1, 2, 1, -4};
  std::cout << demo.threeSumClosest(nums, 1) << std::endl;

  nums = {0,0,0};
  std::cout << demo.threeSumClosest(nums, 1) << std::endl;

  nums = {1,1,1,1};
  std::cout << demo.threeSumClosest(nums, 0) << std::endl;
}
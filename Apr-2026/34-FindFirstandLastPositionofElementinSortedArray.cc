#include <algorithm>
#include <cmath>
#include <csignal>
#include <stdexcept>
#include <vector>

class Solution {
public:
  std::vector<int> searchRange(std::vector<int> &nums, int target) {
    if (nums.size() == 0) {
      return {-1, -1};
    }
    int mid = findAnyX(nums, target);
    if (mid == -1) {
      return {-1, -1};
    }
    return {findFirstX(nums, target, mid), findLastX(nums, target, mid)};
  }

private:
  int findAnyX(std::vector<int> &nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l != r) {
      int i = (l + r) / 2; // l <= i < r
      if (nums[i] == target) {
        return i;
      } else if (nums[i] < target) {
        l = i + 1; // i < r, so (i + 1) CANNOT be larger than r
      } else {
        r = std::max(i - 1, l); // i >= l, so (i - 1) COULD be smaller than l
      }
    }

    // l = r haven't been tested
    if (nums[l] == target) {
      return l;
    }
    return -1;
  }

  int findFirstX(std::vector<int> &nums, int target, int mid) {
    if (nums[mid] != target) {
      throw std::runtime_error("Invalid Argument");
    }

    if (nums.size() == 1) {
      return 0;
    }

    int l = 0, r = mid;
    while (r - l > 1) {
      int i = (l + r) / 2; 
      if (nums[i] == target) {
        r = i; 
      } else {
        l = i;
      }
    }
    if (nums[l] == target) { // incase nums = {2,2}, target = 2
      return l;
    }
    return r;
  }

  int findLastX(std::vector<int> &nums, int target, int mid) {
    if (nums[mid] != target) {
      throw std::runtime_error("Invalid Argument");
    }

    if (nums.size() == 1) {
      return 0;
    }

    int l = mid, r = nums.size() - 1;
    while (r - l > 1) {
      int i = (l + r) / 2; // l < i <= r
      if (nums[i] == target) {
        l = i;
      } else {
        r = i;
      }
    }
    if (nums[r] == target) {
      return r;
    }
    return l;
  }
};
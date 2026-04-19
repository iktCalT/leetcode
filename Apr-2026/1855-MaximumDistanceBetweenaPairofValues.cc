#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
public:
  int maxDistance(std::vector<int> &nums1, std::vector<int> &nums2) {
    /*
     * For each i, find the largest j that makes nums1[i] <= nums2[j]
     *   *binary search
     */
    if (nums1.size() == 0 || nums2.size() == 0) {
      return 0;
    }

    int maxDist = 0;
    int i = 0, j = 0;
    for (; i < nums1.size() && i + maxDist < nums2.size(); i++) {
      if (i > 0 && nums1[i] == nums1[i - 1]) {
        continue;
      }
      if (nums2[i + maxDist] < nums1[i]) {
        continue;
      }

      j = findSmallestNoLessThan(nums2, j, nums1[i]);
      // if the newer j is not larger than the older j, maxDist cannot be larger
      maxDist = std::max(maxDist, j - i);
    }

    return maxDist;
  }

private:
  int findSmallestNoLessThan(const std::vector<int> &nums, int start,
                             int target) {
    // nums must be non-increasing array, e.g. [55,30,5,4,2]
    // retrun index of the smallest number no less than target
    // return -1 if not found
    int l = start, r = nums.size() - 1;
    // Consider special case: (nums[l] >= target) and (nums[r] < target)
    if (nums[l] < target) {
      return -1;
    }
    if (nums[r] >= target) {
      return r;
    }

    while (r - l > 1) {
      int i = (l + r) / 2;
      if (nums[i] < target) {
        r = i;
      } else {
        l = i;
      } // make sure (nums[l] >= target) and (nums[r] < target)
    }
    return l;
  }
};

int main() {
  Solution demo;
  std::vector<int> nums1{55, 30, 5, 4, 2};
  std::vector<int> nums2{100, 20, 10, 10, 5};
  std::cout << demo.maxDistance(nums1, nums2) << std::endl; // 2

  nums1 = {9370, 8977, 8227, 7831, 7761, 7716, 7426, 7309, 6925,
           6515, 6112, 5170, 4720, 3629, 2624, 2583, 1731, 418};
  nums2 = {9633, 9529, 9459, 9282, 9256, 9175, 9169,
           8975, 8880, 8837, 8805, 8747, 8625, 8405};
  std::cout << demo.maxDistance(nums1, nums2) << std::endl;
}
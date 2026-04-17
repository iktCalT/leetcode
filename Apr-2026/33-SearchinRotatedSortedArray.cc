#include <iostream>
#include <ostream>
#include <vector>

class Solution {
public:
  int search(std::vector<int> &nums, int target) {
    if (nums.size() == 0) {
      return -1;
    }

    int k_ = find_k_(nums);
    int len = (int)nums.size();
    int k = len - k_;
    int l = 0;
    int r = len - 1;
    int i;
    while (true) {
      i = convertIndex((l + r) / 2, k, len);
      if (nums[i] == target) {
        return i;
      } else if (nums[i] < target) {
        l = std::min(convertIndex(i, k_, len) + 1, r);
      } else {
        r = std::max(convertIndex(i, k_, len) - 1, l);
      }
      if (r == l)
        break;
    }

    i = convertIndex(l, k, len);
    if (nums[i] == target) {
      return i;
    }

    return -1;
  }

private:
  inline int convertIndex(int i, int k, int size) { return (i + size - k) % size; }

  int find_k_(std::vector<int> &nums) {
    // find k_ (k_ + k = nums.size())
    // If nums is left rotated index k_, it will be in in ascending order again
    // For example, for [4,5,6,7,0,1,2], k = 3, k_ = 4
    int first = nums[0];
    int l = 0, r = nums.size() - 1;
    int k_, i;
    while (true) {
      // We don't need to consider (nums[i] == first), because it's impossible,
      // nums is "with distinct values"
      i = (l + r) / 2;
      if (nums[i] < first)
        r = i;
      else
        l = i;

      if (r - l <= 1)
        break;
    }

    if (nums[l] < nums[r])
      k_ = 0;
    else
      k_ = r;

    return k_;
  }
};

int main() {
  Solution demo;
  std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
  std::cout << demo.search(nums, 0) << std::endl;
  std::cout << demo.search(nums, 3) << std::endl;
}
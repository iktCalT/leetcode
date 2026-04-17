#include <iostream>
#include <vector>

class Solution {
public:
  void nextPermutation(std::vector<int> &nums) {
    if (nums.size() <= 1) {
      return;
    }

    int left = 0;
    for (int i = nums.size() - 1; i - 1 >= 0; i--) {
      if (nums[i - 1] < nums[i]) {
        left = i;
        break;
      }
    }

    if (left == nums.size() - 1) {
      swap(nums[left], nums[left - 1]);
      return;
    }

    // else
    for (int i = left; left != 0 && i < nums.size(); i++) {
      if (nums[left - 1] >= nums[i]) {
        swap(nums[left - 1], nums[i - 1]);
        break;
      }
      if (i == nums.size() - 1) {
        swap(nums[left - 1], nums[i]);
      }
    }
    for (int i = left; i * 2 < left + nums.size() - 1; i++) {
      swap(nums[i], nums[left + nums.size() - 1 - i]);
    }
    return;
  }

private:
  inline void swap(int &i, int &j) {
    int tmp = i;
    i = j;
    j = tmp;
  }
};

void show(std::vector<int> &nums) {
  for (int num : nums) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

int main() {
  Solution demo;
  std::vector<int> nums = {5, 4, 7, 5, 3, 2};
  demo.nextPermutation(nums);
  show(nums);

  nums = {3, 2, 1};
  demo.nextPermutation(nums);
  show(nums);

  nums = {1, 2, 3};
  demo.nextPermutation(nums);
  show(nums);

  nums = {1, 3, 2};
  demo.nextPermutation(nums);
  show(nums);
}
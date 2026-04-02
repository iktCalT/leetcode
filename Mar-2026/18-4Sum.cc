#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::vector<std::vector<int>> results = {};
    if (nums.size() < 4) {
      return results;
    }

    // Sort
    std::sort(nums.begin(), nums.end());

    size_t first, second, third, forth;
    long sum;
    for (first = 0; (long)nums[first]*4 <= target && first < nums.size()-3; first++) {
      if (first != 0 && nums[first] == nums[first-1]) {
        continue;
      }
      for (forth = nums.size() - 1; (long)nums[forth]*4 >= target && forth > first+2; forth--) {
        if (forth != nums.size()-1 && nums[forth] == nums[forth + 1]) {
          continue;
        }
        second = first + 1;
        third = forth - 1;
        while (second < third) {
          sum = (long)nums[first] + nums[second] + nums[third] + nums[forth] - target;
          if (sum == 0) {
            results.insert(results.end(), {nums[first], nums[second], nums[third], nums[forth]});
            indexIncrement(nums, second, third);
            indexDecrement(nums, third, second);
          } else if (sum < 0) {
            indexIncrement(nums, second, third);
          } else {
            indexDecrement(nums, third, second);
          }
        }
      }
    }
    return results;
  }

private:
  void indexIncrement(std::vector<int> &nums, size_t &index, size_t upperBound) {
    do {
      index ++;
    } while (nums[index] == nums[index - 1] && index < upperBound);
  }

  void indexDecrement(std::vector<int> &nums, size_t &index, size_t lowerBound) {
    do {
      index --;
    } while (nums[index] == nums[index + 1] && index > lowerBound);
  }
};

int main() {
  Solution demo = Solution();
  std::vector<int> nums = {1,0,-1,0,-2,2};
  std::vector<std::vector<int>> results = demo.fourSum(nums, 0);
  for (int i = 0; i < results.size(); i++) {
    std::cout << "[";
    for (int j = 0 ; j < results[0].size(); j++) {    
      std::cout << results[i][j] << ", ";
    }
    std::cout << "] ";
  }
  std::cout << std::endl;

  nums = {2,2,2,2,2};
  results = demo.fourSum(nums, 8);
  for (int i = 0; i < results.size(); i++) {
    std::cout << "[";
    for (int j = 0 ; j < results[0].size(); j++) {    
      std::cout << results[i][j] << ", ";
    }
    std::cout << "] ";
  }
  std::cout << std::endl;

  nums = {1000000000,1000000000,1000000000,1000000000};
  results = demo.fourSum(nums, -294967296);
  for (int i = 0; i < results.size(); i++) {
    std::cout << "[";
    for (int j = 0 ; j < results[0].size(); j++) {    
      std::cout << results[i][j] << ", ";
    }
    std::cout << "] ";
  }
  std::cout << std::endl;
}

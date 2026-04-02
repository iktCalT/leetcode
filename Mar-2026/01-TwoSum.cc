#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::vector<int> result = {};
    if (nums.size() < 2) {
      return result;
    }

    std::unordered_map<int, int> demand_map;
    int current = 0;
    // O(n)
    int demand;
    for (; current < nums.size(); current++) {
      // Am I needed?
      if (demand_map.find(nums[current]) != demand_map.end()) {
        // Yeah, someone needs me!
        result = {demand_map[nums[current]], current};
        return result;
      }

      // Add my demand
      demand = target - nums[current];
      if (demand_map.find(demand) == demand_map.end()) {
        // NOT found...
        demand_map[demand] = current;
      } // If found, do nothing, because we only need 1 result
    }
    return result;
  }

  std::vector<int> twoSumAllResults(std::vector<int> &nums, int target) {
    std::vector<int> result = {};
    if (nums.size() < 2) {
      return result;
    }

    std::unordered_map<int, std::vector<size_t>> demand_map;
    size_t current = 0;
    // O(n)
    int demand;
    for (; current < nums.size(); current++) {
      // Am I needed?
      if (demand_map.find(nums[current]) != demand_map.end()) {
        // Yeah, someone needs me!
        for (size_t _ = 0; _ < demand_map[nums[current]].size(); _++) {
          result.insert(result.end(),
                        {(int)demand_map[nums[current]][_], (int)current});
          // It's safe to convert size_t to int
        }
      }

      // Add my demand
      demand = target - nums[current];
      if (demand_map.find(demand) != demand_map.end()) {
        // Found!
        demand_map[demand].insert(demand_map[demand].end(), current);
      } else {
        // NOT found...
        std::vector<size_t> index_list = {current};
        demand_map[demand] = index_list;
      }
    }
    return result;
  }

  // A slower solution
  std::vector<int> twoSumSlow(std::vector<int> &nums, int target) {
    std::vector<int> diffs;
    for (int i = 0; i < nums.size(); i++) {
      auto j = find(diffs.begin(), diffs.end(), nums[i]);
      if (j != diffs.end())
        return {i, (int)distance(diffs.begin(), j)};
      diffs.push_back(target - nums[i]);
    }
    return {-1, -1};
  }
};

int main() {
  Solution demo = Solution();
  std::vector<int> nums = {2, 7, 11, 15};
  int target = 13;
  std::vector<int> result = demo.twoSum(nums, target);
  for (size_t _ = 0; _ < result.size(); _++) {
    std::cout << result[_];
  }
  std::cout << std::endl;

  nums = {3, 2, 5};
  target = 6;
  result = demo.twoSum(nums, target);
  for (size_t _ = 0; _ < result.size(); _++) {
    std::cout << result[_];
  }
  std::cout << std::endl;

  nums = {3, 3, 5, 3};
  target = 6;
  result = demo.twoSum(nums, target);
  for (size_t _ = 0; _ < result.size(); _++) {
    std::cout << result[_];
  }
  std::cout << std::endl;
}
#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <vector>

class Solution {
public:
  int minMirrorPairDistance(std::vector<int> &nums) {
    // If no mirror pair exists, return -1.
    std::map<int, int> wanted;
    int min_dist = INT_MAX;
    for (int i = 0; i < nums.size(); i++) {
      if (wanted.find(nums[i]) != wanted.end()) {
        int dist = i - wanted[nums[i]];
        min_dist = std::min(min_dist, dist);
      }

      // add 
      int reversed = reverse(nums[i]);
      if (wanted.find(reversed) != wanted.end()) {
        wanted[reversed] = i;
      } else {
        wanted.insert({reversed, i});
      }
    }

    return min_dist == INT_MAX ? -1 : min_dist;
  }

  int minMirrorPairDistance_TimeLimitExceeded(std::vector<int> &nums) {
    // Time Limit Exceeded in one test case
    // If no mirror pair exists, return -1.
    std::vector<int> wanted;
    int min_dist = INT_MAX;
    for (int i = 0; i < nums.size(); i++) {
      // reverse find
      auto it = std::find(wanted.rbegin(), wanted.rend(), nums[i]);
      if (it != wanted.rend()) {
        int dist = i - (std::distance(wanted.begin(), it.base()) - 1);
        if (dist < min_dist) {
          min_dist = dist;
        }
      }
      wanted.push_back(reverse(nums[i]));
    }

    return min_dist == INT_MAX ? -1 : min_dist;
  }

private:
  int reverse(int num) {
    int reversed = 0;
    while (num != 0) {
      reversed = reversed * 10 + num % 10;
      num /= 10;
    }
    return reversed;
  }
};

int main() {
  Solution demo;
  std::vector<int> nums = {12,21,45,33,54};
  std::cout << demo.minMirrorPairDistance(nums) << std::endl; // 1

  nums = {12,45,33,54, 12, 21};
  std::cout << demo.minMirrorPairDistance(nums) << std::endl; // 1

  nums = {1};
  std::cout << demo.minMirrorPairDistance(nums) << std::endl; // -1
}
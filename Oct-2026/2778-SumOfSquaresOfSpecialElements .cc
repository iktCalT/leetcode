#include <vector>
class Solution {
public:
  int sumOfSquares(std::vector<int>& nums) {
    int sum = 0;
    int n = nums.size();
    for (const auto [i, num] : std::views::enumerate(nums)) {
      if ((n/(i + 1)) * (i + 1) == n) {
        sum += num * num;
      }
    }
    return sum;
  }
};
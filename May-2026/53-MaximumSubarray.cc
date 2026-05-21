#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // DP
        // For first k elements, the maxSubArray[k] should be 
        // 1. the maxSubArray[k-1]
        // 2. from some point to the newest element
        // 3. k-th element itself (nums[k] and maxSubArray are not adjacent)
        // case 2 and 3 can combine
        int sumMax = nums[0];
        if (nums.size() == 1) return sumMax;

        int sumInterval = max(0, sumMax);
        for (int i = 1; i < nums.size(); ++i) {
            if (sumMax < sumInterval + nums[i]) {
                // case 2
                sumMax = sumInterval + nums[i];
            }
            sumInterval = max(0, sumInterval + nums[i]); // sumInterval >= 0
        }

        return sumMax;
    }
};

int main() {
  Solution demo;
  vector<int> nums{8,-19,5,-4,20};
  std::cout << demo.maxSubArray(nums) << std::endl;
}
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> diffs;
        for (int i=0; i<nums.size(); i++) {
            auto j = find(diffs.begin(), diffs.end(), nums[i]);
            if (j != diffs.end())
                return {i, (int) distance(diffs.begin(), j)};
            diffs.push_back(target - nums[i]);
        }
        return {-1, -1};
    }
};

int main() {
    Solution demo = Solution();
    vector<int> nums = {2,7,11,15};
    int target = 13;
    auto result = demo.twoSum(nums, target);
    printf("[%d, %d]\n", result[0], result[1]);

    nums = {3, 2, 5};
    target = 6;
    result = demo.twoSum(nums, target);
    printf("[%d, %d]\n", result[0], result[1]);
}
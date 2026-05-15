#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        // notice that "All the integers of nums are unique".
        if (nums[0] < nums.back()) return nums[0]; // rorated n (0) times

        int l = 0, r = nums.size() - 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (nums[mid] < nums[r]) {
                r = mid;
            } else if (nums[mid] > nums[l]) {
                l = mid;
            }
        }

        return nums[r];
    }
};
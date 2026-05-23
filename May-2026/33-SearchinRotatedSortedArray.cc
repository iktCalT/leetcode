#include <vector>

class Solution {
public:
    int search(std::vector<int> &nums, int target) {
        // 1. find k -> O(log(n))
        // 2. search -> O(log(n))
        int k = findK(nums);
        int lo = 0;
        int hi = nums.size() - 1;

        while (hi - lo > 1) {
            int rotatedMid = rotateI((lo + hi) / 2, nums.size(), k);
            if (nums[rotatedMid] == target) {
                return rotatedMid;
            } else if (nums[rotatedMid] > target) {
                hi = (hi + lo) / 2;
            } else {
                lo = (hi + lo) / 2;
            }
        }

        if (nums[rotateI(lo, nums.size(), k)] == target) return rotateI(lo, nums.size(), k);
        if (nums[rotateI(hi, nums.size(), k)] == target) return rotateI(hi, nums.size(), k);
        
        return -1;
    }

private:
    int findK (std::vector<int> &nums) {
        int lo = 0, hi = nums.size() - 1;
        // elements in nums are distinct
        if (nums[lo] < nums[hi]) return 0; // although 1 <= k < nums.length

        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (nums[lo] < nums[mid]) {
                lo = mid;
            } else { 
                hi = mid;
            }
        }

        return nums.size() - hi;
    }

    inline int rotateI (const int index, const int size, const int k) {
        return (index + size - k) % size;
    }
};
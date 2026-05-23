#include <vector>
using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        // Iterate from first to last, at most one chance to decrease
        // After decreasing, all members should be no greater than nums[0]
        int descCnt = 0;
        for (auto cit = nums.cbegin() + 1; cit != nums.cend(); ++cit) {
            if (*cit < *(cit - 1)) {
                ++descCnt;
                if (descCnt > 1) return false;
            }
            if (descCnt && *cit > nums.front()) return false;
        }
        return true;
    }
};
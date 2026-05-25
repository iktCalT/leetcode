#include <vector>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        // Notice that F(k) - F(k - 1) = sum(nums) - size * (nums[size - k])
        // where sum(nums) = nums[0] + ... + nums[size - 1]; size = nums.size()

        
        int fk = 0;
        int sum = 0;
        int size = nums.size();
        // calculate f0 and sum(nums)
        for (int i = 0; i < nums.size(); ++i) {
            fk += i * nums[i];
            sum += nums[i];
        }

        int ans = fk;
        for (int k = 1; k < size; ++k) {
            fk = fk + sum - size * nums[size - k];
            ans = max(ans, fk);
        }

        return ans;
    }
};
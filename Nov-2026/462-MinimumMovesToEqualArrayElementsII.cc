#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        // arg min(Sigma_i abs(nums[i] - x)) => x = medium(nums)
        int n = nums.size();
        if (n%2) {
            nth_element(nums.begin(), nums.begin()+(n-1)/2, nums.end());
            int m = nums[(n-1)/2];
            int sum = 0;
            for (const int num : nums) {
                sum += abs(num - m);
            }
            return sum;
        } else {
            nth_element(nums.begin(), nums.begin()+n/2, nums.end());
            int m1 = nums[n/2];
            nth_element(nums.begin(), nums.begin()+n/2-1, nums.end());
            int m2 = nums[n/2-1];
            if (m1 == m2) {
                int sum = 0;
                for (const int num : nums) {
                    sum += abs(num - m1);
                }
                return sum; 
            } else {
                int sum1=0, sum2=0;
                for (const int num : nums) {
                    sum1 += abs(num - m1);
                    sum2 += abs(num - m2);
                }
                return min(sum1, sum2);
            }
        }
    }
};
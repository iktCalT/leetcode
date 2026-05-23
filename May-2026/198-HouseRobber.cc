#include <vector>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        // If we are examing nums[k] (k >= 2)
        // I need to store 2 numbers
        // maxium possible value for 0 to k-2 elements
        // maxium possible value for 0 to k-1 elements
        // Let's call them rob_odd and rob_even

        int rob_even = 0;
        int rob_odd = 0;
        bool is_selected = false;
        for (int i = 0; i < nums.size(); ++i) {
            if (i % 2) {
                // odd
                if (is_selected) { // i-1 is selected -> rob_even cannot add nums[i]
                    if (rob_even >= rob_odd + nums[i]) { 
                        // including "=", to make sure is_selectd is fasle if possible
                        rob_odd = rob_even;
                        is_selected = false;
                    } else {
                        rob_odd += nums[i];
                        is_selected = true;
                    }
                } else { // i-1 is not selected -> both rob_even and rob_odd can add nums[i]
                    rob_odd = max(rob_odd, rob_even) + nums[i];
                    is_selected = true;
                }

            } else {
                // even -> mirror the odd case
                if (is_selected) {
                    if (rob_odd >= rob_even + nums[i]) { 
                        rob_even = rob_odd;
                        is_selected = false;
                    } else {
                        rob_even +=  nums[i];
                        is_selected = true;
                    }
                } else {
                    rob_even = max(rob_odd, rob_even) + nums[i];
                    is_selected = true;
                }
            }
        }

        return max(rob_even, rob_odd);
    }
};


// [1,5,7,4,6,10,3,1]
// [1,5,7,4,6,10,2]
// [1,5,7,4,6,10]
// [1,2,7,4,6,10]
// [1,2,7,3,9,10,1]
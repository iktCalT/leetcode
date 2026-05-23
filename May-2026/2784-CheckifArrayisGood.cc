#include <vector>
using namespace std;

class Solution {
public:
    bool isGood(vector<int>& nums) {
        // If it's a premutation of base(n), it must have n+1 elements 
        //      -> n = nums.size() - 1 (if nums is good)
        int n = nums.size() - 1;
        bool checklist[n + 1];
        for (int i = 0; i < n + 1; i++) {
            checklist[i] = false;
        }
        
        for (int num : nums) {
            if (num < 1 || num > n) return false;

            if (num == n && checklist[n - 1]) {
                num++;
            }

            if (checklist[num - 1]) {
                return false;
            }
            
            checklist[num - 1] = true; 

        }
        return true;
    }
};
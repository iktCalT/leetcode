#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int minElement(vector<int>& nums) {
        int ans = INT_MAX;
        for (int& num : nums) {
            int sum = 0;
            while (num != 0) {
                sum += num % 10;
                num /= 10;
            }
            num = sum;
            ans = min(ans, sum);
        }

        return ans;
    }
};
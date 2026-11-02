#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        // two pointers
        int n = arr.size();
        sort(arr.begin(), arr.end());
        vector<int> ans;
        ans.reserve(k);
        int m = arr[(n - 1) / 2];
        int l = 0, r = n-1;
        while (k != 0 && r >= l) {
            if (arr[r] - m >= m - arr[l]) {
                ans.push_back(arr[r]);
                --r;
            } else {
                ans.push_back(arr[l]);
                ++l;
            }
            --k;
        }

        return ans;
    }
};
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> resultArray(vector<int>& nums) {
    int last1 = nums[0];
    int last2 = nums[1];
    int n = nums.size();
    vector<int> arr1{last1};
    arr1.reserve(n);
    vector<int> arr2{last2};
    arr2.reserve((n + 1) / 2);

    for (int i = 2; i < n; ++i) {
      if (last1 > last2) {
        last1 = nums[i];
        arr1.push_back(last1);
      } else {
        last2 = nums[i];
        arr2.push_back(last2);
      }
    }

    arr1.insert(arr1.end(), arr2.begin(), arr2.end());
    return arr1;
  }
};
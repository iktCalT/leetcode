#include <vector>

using namespace std;

class Solution {
public:
  vector<int> pivotArray(vector<int>& nums, int pivot) {
    // helper array
    vector<int> highs;
    int lo = 0;
    for (int& num : nums) {
      if (num < pivot) {
        nums[lo] = num;
        ++lo;
      } else if (num == pivot) {
        highs.insert(highs.begin(), num);
      } else {
        highs.push_back(num);
      }
    }

    for (int i = lo; i < nums.size(); ++i) {
      nums[i] = highs[i - lo];
    }
    return nums;
  }
};
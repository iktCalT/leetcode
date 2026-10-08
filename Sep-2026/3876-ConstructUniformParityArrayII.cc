#include <vector>
using namespace std;

class Solution {
public:
  bool uniformArray(vector<int>& nums1) {
    // 1. all odd -> true
    // 2. all even -> true

    // 3. some even some odd
    // -> we want to either: 
    // change all even to odd -> nums1[j] must be odd
    // or change all odd to even -> nums1[j] must be odd, too
    // -> the question becomes:
    // if we can find a smallest odd number nums1[j], 
    // to make sure all numbers needs to modify nums1[i]
    // that nums1[i] - nums1[j] >= 1
    // We know that nums1[j] - nums1[j] >= 1 is impossible
    // So, nums1[j] must not change
    // So, the result must be all odd (if nums1 is not all even)
    
    int smallest_odd = INT_MAX;
    int smallest_even = INT_MAX;
    int count_smallest_odd = 1;

    for (int num : nums1) {
      if (num % 2) { // odd
        if (num < smallest_odd) {
          smallest_odd = num;
          count_smallest_odd = 1;
        } else if (num == smallest_odd) {
          ++count_smallest_odd;
        }
      } else {
        smallest_even = min(smallest_even, num);
      }
    }

    // All odd or all even
    if (smallest_odd == INT_MAX || smallest_even == INT_MAX) 
      return true;
    if (smallest_odd < smallest_even && count_smallest_odd == 1) 
      return true;
    return false;
  }
};
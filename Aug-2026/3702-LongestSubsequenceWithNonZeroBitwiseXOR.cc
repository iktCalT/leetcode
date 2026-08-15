#include <vector>
using namespace std;

class Solution {
public:
  int longestSubsequence(vector<int>& nums) {
    // a ^ 0 == a; a ^ 1 == ~a (where a is 0 or 1)
    // So, assume a, b, c, ... are 1-bit numbers
    // a ^ b ^ c ^ d ^ ... = 0 (even number of 1s)
    //                     = 1 (odd number of 1s)
    
    // 1. I take the whole array
    // 2. If it's non-zero, finish, return the size of the array
    // 3. If it's zero, just remove any non-zero element (if has)
    // 4. If all elements are zero, return 0

    int ans = 0; // 0 ^ a ^ b == a ^ b
    bool all_zero = true;
    for (int c : nums) {
      ans ^= c;
      if (all_zero) 
        all_zero = c == 0;
    }

    if (ans != 0) return nums.size();
    if (!all_zero) return nums.size() - 1;
    return 0;
  }
};
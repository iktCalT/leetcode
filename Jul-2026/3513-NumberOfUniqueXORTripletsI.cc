#include <bit>
#include <vector>
using namespace std;

class Solution {
public:
  int uniqueXorTriplets(vector<int>& nums) {
    // Notice that 1 <= n == nums.length <= 10^5
    // So, nums[i]'s highest bit must be 0
    // we have num[0] XOR num[0] == 0
    // 0 XOR num[i] == num[i]
    // So, 1 to n must be in XOR triplet list

    // For each digit: (a XOR b) XOR c = 0
    // means {abc} should be one of: {011},{101},{000},{110}
    // Notice that order is not important! If {xyz} is a
    // candidate, then {yzx}{zxy}{xzy}{zyx}{yxz} are candidates
    // A ^ B ^ C == B ^ C ^ A == C ^ A ^ B == ...

    // So, we just need to know: if there are any 3 i, j, k
    // that makes nums[i] XOR nums[j] XOR nums[k] == 0
    // And we know that 1 XOR 2 XOR 3 is 0.
    // So, as long as n >= 3, 0 must be a candidate

    // Can we get a number greater than n? Sure!
    // e.g. 1 to 10 
    // -> with 1 to 7, we can get 000 to 111 with 
    // only 1 XOR (e.g. get 101 by 001 XOR 100)
    // and we have 1000 -> 1000 ^ (000 to 111) 
    // => we have 0000 to 1111

    size_t n = nums.size();
    if (n <= 2) return n;

    return 1 << bit_width(n);
  }
};
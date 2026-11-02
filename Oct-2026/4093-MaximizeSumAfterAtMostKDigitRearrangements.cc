#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
  long long maximizeSum(vector<int>& nums, int k) {
    long long sum = 0;
    vector<long long> gains;
    gains.reserve(nums.size());
    for (int num : nums) {
      sum += num;
      gains.push_back(gain(num));
    }
    nth_element(gains.begin(), gains.begin()+k, gains.end(), greater<long long>());
    
    return sum + accumulate(gains.begin(), gains.begin()+k, (long long)0);
  }

private:
  long long gain(int num) {
    int original = num;
    
    vector<int> digits;
    digits.reserve(10);
    while (num != 0) {
      digits.push_back(num%10);
      num /= 10;
    }
    sort(digits.begin(), digits.end(), greater<int>());

    long long reorder = 0;
    for (int num : digits) {
      reorder *= 10;
      reorder += num;
    }
    // cout << reorder << "\n";
    return reorder - original;
  }
};
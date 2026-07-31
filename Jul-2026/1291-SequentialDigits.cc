#include <vector>
using namespace std;

class Solution {
public:
  vector<int> sequentialDigits(int low, int high) {
    // 10 <= low <= high <= 10^9
    vector<int> ans;
    
    int max_digits = to_string(high - 1).size();
    for (int digits = 2; digits <= max_digits; ++digits)
      partial(digits, low, high, ans);

    return ans;
  }

private:
  void partial(int digits, int low, int high, 
        vector<int>& ans) {
    // e.g.  digits = 5, low = 12345, high = 54321 
    // means appending sequentialDigits which are 
    // >= 12345 and <= 54321 from 0 to 99999 to ans
    // in ascending order
    if (digits < 2 || digits > 9) return;

    int gap = 0;
    int num = 0;
    for (int i = 0; i < digits; ++i) {
      gap = gap * 10 + 1;
      num = num * 10 + i + 1;
    }

    for (int i = 0; i < 10 - digits; ++i) {
      if (num >= low && num <= high)
        ans.push_back(num);
      num += gap;
    }
  }
};
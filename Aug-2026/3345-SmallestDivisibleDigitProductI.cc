#include <climits>

class Solution {
public:
  int smallestNumber(int n, int t) {
    for (int i = n; i <= INT_MAX; ++i) {
      int product = 1;
      int copy = i;
      while (copy != 0) {
        product *= copy % 10;
        copy /= 10;
      }
      if ((product / t) * t == product) return i;
    }

    return 0;
  }
};
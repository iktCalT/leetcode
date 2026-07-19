#include <algorithm>
using namespace std;

class Solution {
public:
  int sumOfGoodIntegers(int n, int k) {
    int sum = 0;
    for (int i = max(1, n - k); i <= n + k; ++i) {
      sum += (n & i) == 0 ? i : 0;
    }
    return sum;
  }
};
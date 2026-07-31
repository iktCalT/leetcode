#include <cmath>
using namespace std;

class Solution {
public:
  long long sumAndMultiply(int n) {
    int sum = 0;
    long long res = 0;
    int digit = 0;
    while (n != 0) {
      int ones = n % 10;
      if (ones) {
        sum += ones;
        res = res + ones * pow(10, digit);
        ++digit;
      }
      n /= 10;
    }
    return sum * res;
  }
};
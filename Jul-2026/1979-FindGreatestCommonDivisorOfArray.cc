#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
  int findGCD(vector<int>& nums) {
    int m = INT_MAX;
    int M = INT_MIN;
    for (int num : nums) {
      m = min(m, num);
      M = max(M, num);
    }

    return gcd(m, M);

    // Or
    return std::gcd(m, M);
  }

private:
  int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
  }
};
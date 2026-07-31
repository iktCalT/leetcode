#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  long long gcdSum(vector<int>& nums) {
    int mxi = 0; // 1 <= nums[i] <= 10​​​​​​​^9
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      mxi = max(mxi, nums[i]);
      nums[i] = gcd(nums[i], mxi);
    }

    sort(nums.begin(), nums.end());
    long long sum = 0;
    for (int i = 0; i < n - i - 1; ++i) {
      sum += gcd(nums[i], nums[n - 1 - i]);
    }

    return sum;
  }

private:
  /* 62ms */
  int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
  }

  /* 71ms */
  int gcd1(int a, int b) {
    while (a != 0) {
      int tmp = b % a;
      b = a;
      a = tmp;
    }
    return b;
  }

  /* 71ms */
  int gcd0(int a, int b) {
    if (b < a) return gcd(b, a);

    // a <= b
    while ((b / a) * a != b) {
      int tmp = b % a;
      b = a;
      a = tmp;
    }
    return a;
  }

  /* A pretty bad gcd -> TLE */
  int gcd3(int a, int b) {
    if (b < a) return gcd(b, a);

    // a <= b
    while ((b / a) * a != b) {
      int tmp = b - a;
      if (a < tmp) {
        b = tmp;
      } else {
        b = a;
        a = tmp;
      }
    }

    return a;
  }
};

#include <string>

using namespace std;

class Solution {
public:
  string maxSumOfSquares(int num, int sum) {
    // Max score: same number, same sum
    // (a+c)^2 + (b-c)^2 >= a^2+b^2, where a >= b >= c >= 0
    if (sum < 1 || sum > num * 9) return "";

    string ans; ans.reserve(num);
    ans.append(sum/9, '9'); num -= sum/9;
    if (num>0) ans.append(1, '0' + sum%9);
    if (num>1) ans.append(num-1, '0');

    return ans;
  }
};

class Solution0 {
public:
  string maxSumOfSquares(int num, int sum) {
    // Max score: same number, same sum
    // (a+c)^2 + (b-c)^2 >= a^2+b^2, where a >= b >= c >= 0
    if (sum < 1 || sum > num * 9) return "";

    string ans = string(num, '0');
    for (int i = 0; i < num; ++i) {
      if (sum >= 9) {
        ans[i] = '9';
        sum -= 9;
      } else {
        ans[i] = sum + '0';
        sum = 0;
        break;
      }
    }
    return ans;
  }
};
#include <string>
using namespace std;

/* 3ms branchless version of Solution0 */
class Solution {
public:
  bool sumGame(string num) {
    int n = num.size() / 2;

    int qcnt_l = 0;
    int sum_l = 0;

    for (int i = 0; i < n; ++i) {
      sum_l += num[i] - '0';
      qcnt_l += num[i] == '?';
    }

    int qcnt_r = 0;
    int sum_r = 0;

    for (int i = n; i < 2*n; ++i) {
      sum_r += num[i] - '0';
      qcnt_r += num[i] == '?';
    }

    if ((qcnt_l + qcnt_r) % 2) {
      return true;
    } else {
      // sum_r and sum_l are not true above
      // real sum_r = sum_r - qcnt_r * ('?' - '0') + qcnt_r * 4.5;
      //            = sum_r - qcnt_r * ('?' - '0' - 4.5)
      // return sum_r != sum_l become
      // return 2 * sum_r - qcnt_r * (2 * '?' - 2 * '0' - 9) != ...
      return 2 * sum_r - qcnt_r * (2 * '?' - 2 * '0' - 9)
            != 2 * sum_l - qcnt_l * (2 * '?' - 2 * '0' - 9);
    }
  }
};

/* 4ms */
class Solution0 {
public:
  bool sumGame(string num) {
    // Change assume the default value of each
    // '?' is 4.5
    // No matter Alice or Bob choose a '?' on the
    // left or on the right, they can only make the 
    // difference change from -4.5 to +4.5. So, they 
    // can choose any '?', it won't change the result.
    // 
    // e.g. set a left '?' to '0' -4.5; set a right 
    // '?' to '0' +4.5. set a ...

    // To make diff a integer, all number * 2.
    // i.e. 1 is 2; 9 is 18; ? is 9
    int diff = 0;
    int n = num.size() / 2; // num.length is even.

    int qcnt = 0; // count of question mark '?'
    // first half
    for (int i = 0; i < n; ++i) {
      if (num[i] == '?') {
        diff += 9;
        ++qcnt;
      } else {
        diff += 2 * (num[i] - '0');
      }
    }

    // second half
    for (int i = n; i < 2 * n; ++i) {
      if (num[i] == '?') {
        diff -= 9;
        ++qcnt;
      } else {
        diff -= 2 * (num[i] - '0');
      }
    }

    if (qcnt % 2) { // Alice makes the first and last moves
      // Alice must win, she just need to make diff != 0
      // at last step
      return true;
    } else { // Bob makes last move
      // Only when initial diff == 0, bob can win
      return diff != 0;
    }
  }
};
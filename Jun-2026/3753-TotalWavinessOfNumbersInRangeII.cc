#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
  long long totalWaviness(long long num1, long long num2) {
    // f(x0000, x9999) can be written as 
    // g(x, 3)
    //    first parameter: leading digit (it can be 0)
    //    second parameter: number of following 9s

    // f(1234, 4321)  
    //    = f(0, 4321) - f(0, 1233)
    // so, f(0, 4321) 
    //    = g(0, 3) + g(1, 3) + g(2, 3) + g(3, 3)   // to 3999
    //    + g(40, 2) + g(41, 2) + g(42, 2)          // to 4299
    //    + g(430, 1) + g(431, 1)                   // to 4319
    //    + g(4321, 0)                              // to 4321
    return h(num2) - h(num1 - 1);
  }

private:
  long long g(long long x, int n) {
    // return totalWaviness(num1, num2), where
    // num1 = x * 10^n; num2 = (x + 1) * 10^n - 1
    long long cnt = 0;

    // Be careful when x == 0, because 083 actually is not a wavy
    if (x == 0 & n == 0) return 0;
    if (x == 0) {
      // e.g. g(0, 3) -> 000 to 999
      for (int i = 0; i <= 9; ++i) {
        // g(9, 2) + g(8, 2) + ... + g(0, 2)
        // where g(0, 2) = g(9, 1) + g(8, 1) + ...
        cnt += g(i, n - 1);
      }
      return cnt;
    }

    // Normal case: for example, g(184574, 4)
    // how many waviness in x
    // e.g. x = 184574 -> 184, 845, 574 -> 3
    string str = to_string(x);
    long long leading = 0;  // we can delete this variable to make it 
                            // faster, but this is more readable
    for (int i = 2; i < str.size(); ++i) {
      if ((str[i - 1] - str[i - 2]) * (str[i - 1] - str[i]) > 0) {
        ++leading;
      }
    }
    cnt += leading * pow(10, n);

    // extra waviness:
    // notice that 184574(5000) need to plus 1 waviness: 745
    const int last = x % 10;
    if (str.size() >= 2 && n > 0) {
      long long special = 0;
      if (str[str.size() - 2] > str.back()) {
        // ...75 -> 6, 7, 8, 9 -> 4
        special = 9 - last; 
            // if we use str.back(), remember to write (str.back() - '0')
      } else if (str[str.size() - 2] < str.back()) {
        // ...57 -> 0, 1, ..., 6 -> 7
        special = last;
      }
      cnt += special * pow(10, n - 1);
    }

    // extra waviness 2:
    // notice that 184574(5100) need to plus 1 waviness: 451
    // ....a(bc...) if (b > c), a can be 0, 1, ..., b-1; 
    // if b < c, a can be b+1, b+2, ..., 9
    if (n >= 2) {
      long long special_2 = 0;
      // valley: ...7(0)(1-9), 7(1)(2-9), ..., 7(6)(7-9) -> 9 + 8 + 7 + ... + 3
      //    = last * (9 + 10 - last) / 2
      special_2 += (last * (19 - last)) / 2;
      // peak: ...7(8)(0-7), 7(9)(0-8) -> 8 + 9
      //    = (9 - last) * (9 + last + 1) / 2
      special_2 += ((9 - last) * (last + 10)) / 2;
      cnt += special_2 * pow(10, n - 2);
    }

    // how many waviness in 0000 to 9999: a O(1) question
    cnt += tail(n);

    return cnt;
  }

  long long h(long long num) {
    // return totalWaviness(0, num)
    // e.g. 3876 
    //      = g(3876, 0) + g(3875, 0) + ... + g(3870, 0)
    //      + g(386, 1) + g(385, 1) + ... + g(380, 1)
    //      + g(37, 2) + g(36, 2) + ... + g(30, 2)
    //      + g(2, 3) + g(1, 3) + g(0, 3)
    long long cnt = 0;
    int zeros = 0;
    cnt += g(num, zeros); // g(3876, 0)
    while (num != 0) {
      int ones = num % 10;
      --num;
      // 3876, 386, 37, 2
      for (int _ = 0; _ < ones; ++_) {
        printf("calling g(%lld, %d), result:(%lld)\n", num, zeros, g(num, zeros));
        cnt += g(num, zeros); // g(3875, 0), g(3874, 0), ..., g(3870, 0)
        --num;
      }
      // 3869, 379, 29, -1
      num = (num + 1) / 10; // in case num starts with 1
      // 386, 38, 3, 0
      ++zeros;
    }
    return cnt;
  }

  unordered_map<int, long long> check_table = {{0, 0}, {1, 0}, {2, 0}};
  long long tail(int n) {
    // if n = 4, return the number of waviness from 0000 to 9999
    // leading 0s are included (meaning 0813 is 2: 081 and 813)
    if (check_table.contains(n)) return check_table[n];
    long long ans = 0;
    if (n == 3) {
      for (int i = 1; i <= 9; ++i) {
        ans += 2 * i * i;
      }
    } else {
      ans =  tail(n - 1) * 10 + tail(3) * pow(10, n - 3);
    }

    check_table.insert({n, ans});
    return ans;
  }
};

int main() {
  Solution demo;
  std::cout << demo.totalWaviness(1, 98765432109876) << "\n"; // 671319920770693
}
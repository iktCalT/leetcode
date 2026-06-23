#include <vector>

using namespace std;

class Solution {
public:
  int lastRemaining(int n) {
    // 1. delete 1 + 2 * k
    // 2. if n is even: delete n - 1 - 4 * k
    //    if n is odd: delete n - 4 * k
    // -> remaining numbers: 
    //    4 * k + 2 (n == 4 * m or n == 4 * m + 1)
    //    4 * k.    (n == 4 * m + 2 or n == 4 * m + 3)
    // binary representation 4 * k + 2 -> ****10; 4 * k -> ****00

    // for example: n = 16 (4 * m)
    // after going right, 2,4(0100),6,8(1000),10,12(1100),14,16(1 0000) -> (***0)
    // now 2, 4, 6, 8, 10, 12, 14 16 are new 1 to 8
    // new number = (old number >> 1)
    // is_even = 1

    // after going left, 1, 3, 5, 7
    // now 1, 3, 5, 7 are the new 1(001), 2(010), 3(011), 4(100)
    // new number = (old number + is_even) >> 1

    // Initially, n numbers 
    // -> go right: n = floor(n/2)
    // -> go left: n = floor(n/2)
    
    // Reverse: 
    // The last state [number], it can be viewed as new "1"

    vector<bool> even;
    while (n != 1) {
      even.push_back(!(n % 2));
      n = n >> 1;
    }

    int ans = 1;
    for (int i = even.size() - 1; i >= 0; --i) {
      if (i % 2) {
        // if i is odd: reverse left
        ans = ans << 1;
        ans -= even[i];
      } else {
        // if i is even: reverse right
        ans = ans << 1;
      }
    }

    return ans;
  }
};
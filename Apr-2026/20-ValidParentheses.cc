#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>

class Solution {
public:
  bool isValid(std::string s) {
    std::vector<char> lp = {'(', '[', '{'}; // left parentheses
    std::vector<char> rp = {')', ']', '}'}; // right parentheses
    std::stack<char> stk;                   // stack
    char c, lc;                             // char and last char
    for (size_t _ = 0; _ < s.length(); _++) {
      c = s[_];
      if (std::find(lp.begin(), lp.end(), c) != lp.end()) {
        stk.push(c);
      } else if (std::find(rp.begin(), rp.end(), c) != rp.end()) {
        if (stk.empty()) {
          return false;
        }
        lc = stk.top();
        if (std::find(rp.begin(), rp.end(), c) - rp.begin() ==
            std::find(lp.begin(), lp.end(), lc) - lp.begin()) {
          // If c and lc is a pair of parentheses
          stk.pop();
        } else {
          stk.push(c);
        }
      } else {
        return false;
      }
    }

    return stk.empty();
  }
};

int main() {
  Solution demo = Solution();
  printf("%d\n", demo.isValid("()[{}]"));
  printf("%d\n", demo.isValid("([{}]"));
  printf("%d\n", demo.isValid("]"));
}
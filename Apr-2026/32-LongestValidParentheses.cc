#include <algorithm>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>

class Solution {
private:
  struct Parenteses {
    int left;
    int right;
    Parenteses(int left, int right) : left(left), right(right){};
    int getLength() { return right - left + 1; }
  };

public:
  int longestValidParentheses(std::string s) {
    int max_len = 0;
    if (s.length() < 2)
      return max_len;

    // I need 1 sets of indexes and 2 indexes:
    // previous parentheses set (store in stack)
    // current left, current right
    std::stack<Parenteses> spre; // spre: Stack of PREvious parentheses
    int left, right;
    int cur_len;
    bool is_current_valid = false;

    for (right = 0; right < s.length(); right++) {
      if (!is_current_valid) {
        if (findFirstValid(left, right, s, right)) {
          is_current_valid = true;
          cur_len = 2;
          while (combineParentheses(left, cur_len, spre)) {}
          max_len = std::max(cur_len, max_len);
          continue;
        } else {
          break;
        }
      }

      if (!(s[right] == ')' && left > 0 && s[left - 1] == '(')) {
        is_current_valid = false;
        cur_len = 0;
        spre.push(Parenteses{left, right - 1});
      } else {
        is_current_valid = true;
        left--;
        cur_len += 2;
        while (combineParentheses(left, cur_len, spre)) {}
        max_len = std::max(cur_len, max_len);
      }
    }
    return max_len;
  }

private:
  inline bool findFirstValid(int &left, int &right, const std::string &s,
                             int start) {
    // find first valid pair from start
    // return true if found; return false if not found
    for (right = start; right < s.length(); right++) {
      if (s[right] == ')' && right > 0 && s[right - 1] == '(') {
        left = right - 1;
        return true;
      }
    }
    return false;
  }

  bool combineParentheses (int &left, int &cur_len, std::stack<Parenteses> &spre) {
    if (!spre.empty() && left - 1 == spre.top().right) {
      // concatenate two Parenteses
      auto p = spre.top();
      spre.pop();
      left = p.left;
      cur_len = cur_len + p.getLength();
      return true;
    }
    return false;
  }
};

int main() {
  Solution demo;
  std::cout << demo.longestValidParentheses("(()") << std::endl;      // 2
  std::cout << demo.longestValidParentheses(")()())") << std::endl;   // 4
  std::cout << demo.longestValidParentheses("(") << std::endl;        // 0
  std::cout << demo.longestValidParentheses("") << std::endl;         // 0
  std::cout << demo.longestValidParentheses("(()()())") << std::endl; // 8
  std::cout << demo.longestValidParentheses("(((((((())))())))())")
            << std::endl; // 20
  std::cout << demo.longestValidParentheses("(((((((())))(())))())")
            << std::endl; // 20
  std::cout << demo.longestValidParentheses("(())()))()(((())((()))))")
            << std::endl; // 16
}
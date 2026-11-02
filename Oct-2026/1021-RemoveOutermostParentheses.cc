#include <string>
using namespace std;

// 0ms
class Solution {
public:
  string removeOuterParentheses(string s) {
    // ASCII: '(' -> 40; ')' -> 41
    string ans;
    ans.reserve(s.size());
    for (const char c : s) {
      // depth == 0 && c=='(', ignore
      // depth == 1 && c==')', ignore
      // => depth + '(' - c == 0, ignore
      static int depth = 0;
      if (depth + '(' - c) { ans += c; };
      depth += c == '(' ? 1 : -1;
    }
    return ans;
  }
};

// 1ms
class Solution1 {
public:
  string removeOuterParentheses(string s) {
    // Find primitives strings
    string ans;
    ans.reserve(s.size());
    int depth = 0;
    for (const char c : s) {
      switch (c) {
      case '(':
        if (depth != 0) {
          ans += '(';
        }
        ++depth;
        break;
      case ')':
        --depth;
        if (depth != 0) { // exit a primitive string
          ans += ')';
        }
        break;
      default:
      }
    }
    return ans;
  }
};

// 5ms
class Solution0 {
public:
  string removeOuterParentheses(string s) {
    // Find primitives strings
    int depth = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
      switch (*it) {
      case '(':
        if (depth == 0) {
          it = --s.erase(it);  // remove the start '('
        }
        ++depth;
        break;
      case ')':
        --depth;
        if (depth == 0) { // exit a primitive string
          it = --s.erase(it);    // remove the last ')'
        }
        break;
      default:
      }
    }
    return s;
  }
};
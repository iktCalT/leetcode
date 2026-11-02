#include <string>

// 1ms
class Solution {
public:
  int minInsertions(std::string s) {
    // From right to left, count the 2 * #')' - #'('
    int net = 0;
    int added = 0;
    for (auto crit = s.crbegin(); crit != s.crend(); ++crit) {
      switch (*crit) {
      case ')':
        ++net;
        break;
      default:
        added += net % 2;
        net += net % 2;

        net -= 2;
        added += net < 0 ? 2 : 0;
        net += net < 0 ? 2 : 0;
      }
    }

    added += net % 2;
    net += net % 2;

    return added + net / 2;
  }
};

// 7ms
class Solution0 {
public:
  int minInsertions(std::string s) {
    // From right to left, count the 2 * #')' - #'('
    int net = 0;
    int added = 0;
    for (auto crit = s.crbegin(); crit != s.crend(); ++crit) {
      switch (*crit) {
      case ')':
        ++net;
        break;
      default:
        if (net % 2) {
          // not pairs of ')' -> add 1 ')'
          ++net;
          ++added;
        }

        net -= 2;
        if (net < 0) {
          // not enough pairs of ')' -> add 2 ')'s
          net += 2;
          added += 2;
        }
      }
    }

    if (net % 2) {
      // not pairs of ')' -> add 1 ')'
      ++net;
      ++added;
    }
    if (net > 0) {
      // not enough '(' -> add net/2 '('s
      added += net/2;
    }

    return added;
  }
};
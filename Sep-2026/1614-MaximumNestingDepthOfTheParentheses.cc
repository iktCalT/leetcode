#include <string>
using namespace std;

class Solution {
public:
  int maxDepth(string s) {
    int depth = 0;
    int max_depth = 0;
    for (const char c : s) {
      switch (c) {
      case '(':
        depth += 1;
        max_depth = max(max_depth, depth);
        break;
      case ')':
        depth -= 1;
      }
    }
    return max_depth;
  }
};
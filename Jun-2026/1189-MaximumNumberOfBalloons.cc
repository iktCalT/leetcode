#include <algorithm>
#include <array>
#include <string>

class Solution {
public:
  int maxNumberOfBalloons(std::string text) {
    // store count of 'a', 'b', 'l', 'n', 'o'
    std::array<int, 5> count = {0, 0, 0, 0, 0};
    for (const char c : text) {
      switch (c) {
      case 'a':
        ++count[0];
        break;
      case 'b':
        ++count[1];
        break;
      case 'l':
        ++count[2];
        break;
      case 'n':
        ++count[3];
        break;
      case  'o':
        ++count[4];
        break;
      default:
        // do nothing
      }
    }

    count[2] /= 2; // 'l'
    count[4] /= 2; // 'o'

    int ans = count[0];
    for (int i = 1; i < 5; ++i) {
      ans = std::min(ans, count[i]);
    }
    return ans;
  }
};
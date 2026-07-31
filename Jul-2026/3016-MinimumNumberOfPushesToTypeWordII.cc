#include <algorithm>
#include <array>
#include <string>
using namespace std;

class Solution {
public:
  int minimumPushes(string word) {
    // Letters occur most frequently are the first letter of 2 - 9
    array<int, 26> count;
    fill(count.begin(), count.end(), 0);
    for (char c : word) {
      ++count[c - 'a'];
    }

    int ans = 0;
    sort(count.begin(), count.end(), std::greater<int>());
    for (int i = 0; i < 26; i += 8) {
      int upper = min(26 - i, 8);
      for (int j = 0; j < upper; ++j) {
        ans += count[i + j] * (i / 8 + 1);
      }
    }
    return ans;
  }
};
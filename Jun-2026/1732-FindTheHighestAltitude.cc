#include <algorithm>
#include <vector>

class Solution {
public:
  int largestAltitude(std::vector<int>& gain) {
    int alt = 0;
    int max_alt = 0;
    for (int da : gain) {
      alt += da;
      max_alt = std::max(max_alt, alt);
    }
    return max_alt;
  }
};
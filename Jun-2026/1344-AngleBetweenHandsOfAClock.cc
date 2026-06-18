#include <algorithm>

#define MNT 60
#define HR 12

class Solution {
public:
  double angleClock(int hour, int minutes) {
    double degree_m = 360.0 / MNT * minutes;
    double degree_h = 360.0 / HR * hour + 360.0 / (HR * MNT) * minutes;
    double angle = std::abs(degree_m - degree_h);
    return std::min(angle, 360 - angle);
  }
};
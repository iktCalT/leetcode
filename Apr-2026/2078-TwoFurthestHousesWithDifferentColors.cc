#include <algorithm>
#include <map>
#include <iostream>
#include <vector>

class Solution {
public:
  int maxDistance(std::vector<int> &colors) {
    int max_dist = 0;
    if (colors.size() == 0) {
      return max_dist;
    }

    std::map<int, int> first_two_colors;
    std::map<int, int> last_two_colors;

    findFirstTwoColors(colors, first_two_colors, false);
    if (first_two_colors.size() == 1) {
      return max_dist;
    }
    findFirstTwoColors(colors, last_two_colors, true);

    for (auto first : first_two_colors) {
      for (auto last : last_two_colors) {
        if (first.first != last.first) {
          // if different color
          int dist = last.second - first.second;
          max_dist = std::max(max_dist, dist);
        }
      }
    }

    return max_dist;
  }

private:
  void findFirstTwoColors(std::vector<int> &colors,
                          std::map<int, int> &first_two_colors, bool is_reverse) {
    for (int i = 0; i < colors.size(); i++) {
      int index = is_reverse ? colors.size() - 1 - i : i;
      if (first_two_colors.find(colors[index]) == first_two_colors.end()) {
        // doesn't exits
        first_two_colors.insert(first_two_colors.begin(), {colors[index], index});
        if (first_two_colors.size() == 2) {
          break;
        }
      }
    }
  }
};


int main() {
  Solution demo;
  std::vector<int> colors{1,1,1,6,1,1,1}; 
  std::cout << demo.maxDistance(colors) << std::endl;
}
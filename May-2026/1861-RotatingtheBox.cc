#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<char>> rotateTheBox(vector<vector<char>> &boxGrid) {
    // 'Fall' in RIGHT direction, then rotate -> to make use of spacial locality
    fall2Right(boxGrid);
    return rotate90(boxGrid);
  }

private:
  void fall2Right(vector<vector<char>> &boxGrid) {
    for (auto &row : boxGrid) {
      auto obstacle = row.rbegin() - 1;
      for (auto rit = row.rbegin(); rit != row.rend(); rit++) {
        if (*rit == '#') { // stone
          *rit = '.';      // set to empty then place the stone, in case rit ==
                           // obstacle + 1
          obstacle++;
          *obstacle = '#';
        } else if (*rit == '*') { // stationary obstacle
          obstacle = rit;
        } // else: do nothing
      }
    }
  }

  vector<vector<char>> rotate90(const vector<vector<char>> &boxGrid) {
    vector<vector<char>> rotatedBoxGrid;
    rotatedBoxGrid.reserve(boxGrid[0].size());

    for (int i = 0; i < rotatedBoxGrid.capacity(); i++) {
      // initialize row
      rotatedBoxGrid.emplace_back();
      rotatedBoxGrid.back().reserve(boxGrid.size());

      for (int j = 0; j < rotatedBoxGrid.back().capacity(); j++) {
        rotatedBoxGrid.back().push_back(boxGrid[boxGrid.size() - 1 - j][i]);
      }
    }

    return rotatedBoxGrid;
  }
};

int main() {
  Solution demo;
  vector<vector<char>> test{{'#', '.', '#'}};
  demo.rotateTheBox(test);
}
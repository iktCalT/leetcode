#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;

class Solution {
public:
  void rotate(vector<vector<int>> &matrix) {
    int n = matrix.size();
    if (n <= 0 || n != matrix[0].size()) {
      throw runtime_error("Invalid argument");
    }
    for (int i = 0; i < floor(n / 2.0f); i++) {
      for (int j = 0; j < ceil(n / 2.0f); j++) {
        int tmp = matrix[i][j];
        for (int _ = 0; _ < 4; _++) {
          coordinateConversion(i, j, n);
          swap(matrix[i][j], tmp);
        }
      }
    }
  }

private:
  inline void coordinateConversion(int &i, int &j, int n) {
    // 1. original point: ((n-1)/2, (n-1)/2), new coordinate: (i-(n-1)/2,
    // j-(n-1)/2)
    // 2. rotate: (j-(n-1)/2, (n-1)/2-i)
    // 3. old coordinates: (j, (n-1)-i)
    int tmp = i;
    i = j;
    j = n - 1 - tmp;
  }
  inline void swap(int &i, int &j) {
    int tmp = i;
    i = j;
    j = tmp;
  }
};
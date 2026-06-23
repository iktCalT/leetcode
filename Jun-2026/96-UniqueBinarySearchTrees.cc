#include <vector>

using namespace std;

class Solution {
public:
  int numTrees(int n) {
    // DP
    // if we choose 1 as root, left subtree has 0 member, while right
    // subtree has n-1 members -> numTrees(0) * numTrees(n-1)
    // if we choose i as root, numTrees(i-1) * numTrees(n-i)
    // numTrees(n) = Σi(numTrees(i-1) * numTrees(n-i))
    vector<int> result(n + 1, 0);
    result[0] = 1;
    result[1] = 1;
    for (int m = 2; m <= n; ++m) {
      int i = 1;
      for (; i - 1 < m - i; ++i) {
        result[m] += 2 * result[i - 1] * result[m - i];
      }
      if (i - 1 == m - i) result[m] += result[i - 1] * result[i - 1];
    }
    return result.back();
  }
};
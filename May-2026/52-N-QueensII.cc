#include <algorithm>
#include <vector>

class Solution {
public:
  int totalNQueens(int n) {
    // DFS
    // Every row / column should have exactly 1 queen

    // helpers
    std::vector<int> occ(n, -1); // occupied cols: 0 to n-1
    std::vector<int> rpc(n, -1); // row + col: 0 to 2*(n-1)
    std::vector<int> rmc(n, -n); // row - col: -(n-1) to (n-1)
    occ.reserve(n); rpc.reserve(n); rmc.reserve(n);

    int cnt = 0;
    placeQueen(0, n, cnt, false, occ, rpc, rmc);
    return cnt;
  }

private:
  void placeQueen(int irow, int n, int& cnt, bool middle,
                  std::vector<int> &occ, std::vector<int> &rpc,
                  std::vector<int> &rmc) {
    
    for (int icol = 0; icol < n; ++icol) {
      if (irow == 0 && icol * 2 > n + 1) break;
      if (irow == 0 && icol * 2 == n + 1) middle = true;      

      // Skip un-placeable positions
      if ((std::find(occ.begin(), occ.end(), icol) != occ.end()) ||
          (std::find(rpc.begin(), rpc.end(), irow + icol) != rpc.end()) ||
          (std::find(rmc.begin(), rmc.end(), irow - icol) != rmc.end()))
        continue;

      // Place queen
      occ.push_back(icol);
      rpc.push_back(irow + icol);
      rmc.push_back(irow - icol);

      // Next row
      if (irow == n - 1) {
        if (middle) cnt += 1;
        else cnt += 2;
      } else {
        placeQueen(irow + 1, n, cnt, middle, occ, rpc, rmc);
      }

      // Restore
      rmc.pop_back();
      rpc.pop_back();
      occ.pop_back();
    }
  }
};
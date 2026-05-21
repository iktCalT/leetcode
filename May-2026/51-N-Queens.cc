#include <algorithm>
#include <string>
#include <vector>

class Solution {
private:
  std::vector<std::vector<std::string>> ans;

public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    // DFS
    // Every row / column should have exactly 1 queen

    std::vector<std::string> board;
    std::string line;
    line.append(n, '.');
    board = std::vector<std::string>(n, line);
    // helpers
    std::vector<int> occ(n, -1); // occupied cols: 0 to n-1
    std::vector<int> rpc(n, -1); // row + col: 0 to 2*(n-1)
    std::vector<int> rmc(n, -n); // row - col: -(n-1) to (n-1)
    occ.reserve(n); rpc.reserve(n); rmc.reserve(n);

    placeQueen(0, board, occ, rpc, rmc);
    return ans;
  }

private:
  void placeQueen(int irow, std::vector<std::string> &board,
                  std::vector<int> &occ, std::vector<int> &rpc,
                  std::vector<int> &rmc) {
    //
    std::string &row = board[irow];
    for (int icol = 0; icol < row.size(); ++icol) {
      // Skip un-placeable positions
      if ((std::find(occ.begin(), occ.end(), icol) != occ.end()) ||
          (std::find(rpc.begin(), rpc.end(), irow + icol) != rpc.end()) ||
          (std::find(rmc.begin(), rmc.end(), irow - icol) != rmc.end()))
        continue;

      // Place queen
      board[irow][icol] = 'Q';
      occ.push_back(icol);
      rpc.push_back(irow + icol);
      rmc.push_back(irow - icol);

      // Next row
      if (irow == board.size() - 1) {
        ans.push_back(board);
      } else {
        placeQueen(irow + 1, board, occ, rpc, rmc);
      }

      // Restore
      rmc.pop_back();
      rpc.pop_back();
      occ.pop_back();
      board[irow][icol] = '.';
    }
  }
};
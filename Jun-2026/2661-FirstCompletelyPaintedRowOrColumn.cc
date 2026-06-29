#include <vector>
using namespace std;

struct Cell {
  int r;
  int c;
};

class Solution {
public:
  int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
    // O(m * n)
    int m = mat.size(); // 1 <= m <= 10^5
    int n = mat[0].size(); // 1 <= n <= 10^5
    // a quick check table
    vector<Cell> tab(m * n + 1);
    for (int r = 0; r < m; ++r) {
      for (int c = 0; c < n; ++c) {
        tab[mat[r][c]] = {r, c};
      }
    }

    vector<int> rows(m, n); // rows[i]: number of unpainted cells on row i
    vector<int> cols(n, m);

    for (int i = 0; i < m * n; ++i) {
      Cell pos = tab[arr[i]];
      if (--rows[pos.r] == 0 || --cols[pos.c] == 0) return i;
    }

    return -1; // error
  }
};
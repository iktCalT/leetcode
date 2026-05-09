#include <stdexcept>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        if (grid.size() < 0 || grid[0].size() < 0 || grid.size() % 2 || grid[0].size() % 2) {
            throw runtime_error("Invalid grid");
        }

        for (int layer = 0; layer < min(grid.size(), grid[0].size()) / 2; layer++) {
            rotateLayer(grid, layer, k);
        }
        return grid;
    }
private:
    void rotateLayer(vector<vector<int>>& grid, const int layer, int k) {
        // 0 <= layer < min(m, n) / 2, where m = number of row, n = number of columns
        if (layer < 0 || layer >= min(grid.size(), grid[0].size()) / 2) {
            throw runtime_error("Invalid layer");
        }

        // initialization
        int rs = layer, cs = layer; // r: row; c: column; s: start; n: number of
        int nr = grid.size() - 2 * layer;
        int nc = grid[0].size() - 2 * layer;
        int size = 2 * (nr + nc - 2);
        k %= size; // 0 <= k < size

        // generate 1D vector
        vector<int> line;
        line.reserve(size);
        for (int i = 0; i < line.capacity(); i++) {
          auto [rr, rc] = to2DCor(i, nr, nc);
          line.push_back(grid[rr + layer][rc + layer]);
        }

        // rotate k steps
        vector<int> split_line{line.begin(), line.begin() + k};
        line.erase(line.begin(), line.begin() + k);
        line.insert(line.end(), split_line.begin(), split_line.end());

        // fill the grid with modified line
        for (int i = 0; i < line.size(); i++) {
          auto [rr, rc] = to2DCor(i, nr, nc);
          grid[rr + layer][rc + layer] = line[i];
        }
    }

    // int to1DCor (int rr, int rc, int nr, int nc) {
    //     // rr: relative row; rc: relative col; nr: number of rows; nc: number of cols
    //     int cor = 0; // 1D coordinate
    //     if (rr == 0 || rc == nc - 1) {
    //         return rr + rc;
    //     } else if (rr == nr - 1 || rc == 0) {
    //         return 2 * (nr + nc - 2) - rr - rc;
    //     } else {
    //         throw runtime_error("Invalid coordinates");
    //     }
    // }

    pair<int, int> to2DCor (int cor, int nr, int nc) {
        if (cor <= nc - 1) {
            return {0, cor};
        } else if (cor <= nr + nc - 2) {
            return {cor - (nc - 1), nc - 1};
        } else if (cor <= nr + 2 * nc - 3) {
            return {nr - 1, (nr + 2 * nc - 3) - cor};
        } else {
            return {2 * (nr + nc - 2) - cor, 0};
        }
    }
};

int main() {
  Solution demo;
  vector<vector<int>> grid{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
  demo.rotateGrid(grid, 2);
}
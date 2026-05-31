#include <iostream>
#include <vector>
using namespace std;

class Solution { // Runtime 8 ms Beats 63.94%; Memory 31.10 MB Beats 37.31%
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        // record how many ones in a row for each position
        // e.g. {1, 0, 1, 1, 1} -> {1, 0, 3, 2, 1}
        vector<vector<int>> record(matrix.size(), vector<int>(matrix[0].size(), 0));
        for (int row = 0; row < matrix.size(); ++row) {
            int cnt = 0;
            for (int col = matrix[0].size() - 1; col >= 0; --col) {
                if (matrix[row][col] != '1') {
                    cnt = 0;
                    continue;
                }
                ++cnt;
                record[row][col] = cnt;
            }
        }

        int len = 0;
        for (int row = 0; row < matrix.size(); ++row) {
            for (int col = 0; col < matrix[0].size(); ++col) {
                if (record[row][col] > len) {
                    len = max(len, maxSquare(row, col, record));
                }
            }
        }

        return len * len;
    }

private:
    int maxSquare(int row, int col, vector<vector<int>>& record) {
        int width = record[row][col];
        int height = 1;
        while (height < width) {
            if (row + height >= record.size()) {
                width = min(width, height);
                break;
            }

            width = min(width, record[row + height][col]);
            ++height;
        }

        return width;
    }
};

class SolutionSlow { // Runtime 52 ms Beats 6.78%; Memory 27.02 MB Beats 99.84%
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        // Start from length = 1, and scan each position
        // Once there is a square can hold a length = k
        // square, length++ and continue seeking.
        // We don't need to go back, because previous 
        // positions cannot only hold squares smaller than
        // k * k. return (length - 1) * (length - 1)
        int length = 1;

        // 1 <= m, n <= 300
        for (int r = 0; r < matrix.size(); ++r) {
            for (int c = 0; c < matrix[0].size(); ++c) {
                if (exceedBoundry(r, c, length, matrix)) 
                    break;
                if (matrix[r][c] != '1') 
                    continue;

                if (canHold(r, c, length, matrix)) {
                    ++length;
                    while (canExpand(r, c, length, matrix)) {
                        ++length;
                    }
                }
            }
        }

        return (length - 1) * (length - 1);
    }

private:
    inline bool exceedBoundry (int r, int c, int length, vector<vector<char>>& matrix) {
        return (r + length > matrix.size() || c + length > matrix[0].size());
    }

    bool canHold(int r, int c, int length, vector<vector<char>>& matrix) {
        if (exceedBoundry(r, c, length, matrix)) 
            return false;

        for (int i = r; i < r + length; ++i) {
            for (int j = c; j < c + length; ++j) {
                if (matrix[i][j] != '1')
                    return false;
            }
        }

        return true;
    }

    bool canExpand(int r, int c, int length, vector<vector<char>>& matrix) {
        // we already know that this postion han hold 
        // (length - 1)^2 square
        if (exceedBoundry(r, c, length, matrix)) 
            return false;

        int i, j;

        // bottom row (include matrix[r + length - 1][c + length - 1], high spacial locality)
        i = r + length - 1;
        for (int j = c; j < c + length; ++j) {
            if (matrix[i][j] != '1')
                return false;
        }

        // right col (not include matrix[r + length - 1][c + length - 1], low spacial locality)
        j = c + length - 1;
        for (int i = r; i < r + length - 1; ++i) {
            if (matrix[i][j] != '1')
                return false;
        }

        return true;
    }
};

/* class SolutionDiscarded {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        // I need to record all '1's -> For each row, I'll have a ordered map, 
        // key is number of consecutive '1's, and value is starting postion
        vector<map<int, int, greater<int>>> ones_map(matrix.size());
        // O(m * n)
        for (int r = 0; r < matrix.size(); ++r) {
            const vector<char>& row = matrix[r];
            
            for (int c = 0; c < row.size(); ) {
                if (row[c] != '1') {
                    ++c;
                    continue;
                }
                
                // row[j] == '1'
                int start = c;
                int cnt = 1;
                ++c;
                while (c < row.size() && row[c] == '1') {
                    ++cnt;
                    ++c;
                }
                ones_map[r].insert({cnt, start});
            }
        }

        int length = 0;
        // O(m)
        for (auto& row : ones_map) {
            if (!row.empty())
                length = max(length, row.begin()->first);
        }

        while (length > 0) {
            for (int r = 0; r < ones_map.size(); ++r) {
                // TODO
            }
        }

        return length * length;
    }
}; */

int main() {
  Solution demo;
  vector<vector<char>> m{{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
  std::cout << demo.maximalSquare(m) << "\n";
}
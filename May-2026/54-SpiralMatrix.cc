#include <vector>
using namespace std;

class Solution {
public:
    #define VISITED 101
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        ans.reserve(matrix.size() * matrix[0].size());
        pair<int, int> direction{1, 0};
        int i = 0, j = 0;
        while(true) {
            if (i >= matrix.size() || j >= matrix[0].size() || matrix[i][j] == VISITED) break;

            if (matrix[i][j] != VISITED) { // visited positions are set to 101 (VISITED)
                ans.push_back(matrix[i][j]);
                matrix[i][j] = VISITED;
            }

            if (i + direction.second >= matrix.size() 
                || j + direction.first >= matrix[0].size()
                || matrix[i + direction.second][j + direction.first] == VISITED) {
                turnRight(direction);
            }

            i += direction.second;
            j += direction.first;
        }
        return ans;
    }

private:
    void turnRight(pair<int, int>& direction) {
        // new_x = -y; new_y = x
        int first = direction.first;
        direction.first = -direction.second;
        direction.second = first;
    }
};
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        // DFS
        // Be careful: 0 <= stones[i] <= INT_MAX -> [0, 1, 3, 6, 10, 15, ..., INT_MAX]
        // The first jump must from 0 to 1 (cannot be 2), so just start from 1
        if (stones.size() < 2 || stones[1] != 1) return false;
        visited = vector<vector<int>>(stones.size());
        return Jump(stones, 1, 1);
    }

private:
    vector<vector<int>> visited;
    bool Jump(vector<int>& stones, int pos, int k) {
        if (pos == stones.size() - 1) return true;
        if (find(visited[pos].begin(), visited[pos].end(), k) != visited[pos].end()) {
          return false;
        } else {
          visited[pos].push_back(k);
        }

        array<int, 3> actions{0, 0, 0};
        for (int next = pos + 1 ; next < stones.size(); ++next) {

            // Don't write stones[pos] + k - 1, it may be greater than INT_MAX
            if (stones[next] - (k - 1) < stones[pos]) { 
                continue;
            } else if (stones[next] - (k - 1) == stones[pos]) {
                // Don't need to write "if (k == 1)":
                // if k == 1 -> stones[next] == stones[pos], this is impossible 
                // because next > pos, and stones is sorted in a strictly increasing order
                actions[0] = next;
            } else if (stones[next] - k == stones[pos]) {
                actions[1] = next;
            } else if (stones[next] - (k + 1) == stones[pos]) {
                actions[2] = next;
                break;
            } else { 
                break;
            }
        }

        // Try k + 1, then k, then k - 1 (in case [0,1,2,3,4,5,6,7....])
        for (int i = actions.size() - 1; i >= 0; --i) { // actions.size() - 1 = 2
            int& next = actions[i];
            if (next > 0 && Jump(stones, next, k - 1 + i)) return true;
        }

        return false;
    }
};

int main() {
  Solution demo;
  vector<int> stones{0,1,3,5,6,8,12,17};
  std::cout << demo.canCross(stones) << "\n";
}
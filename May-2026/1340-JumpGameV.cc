#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // max distance: d
    // cannot pass barrier higher than starting point
    int maxJumps(vector<int>& arr, int d) {
        // Maintain a vector storing max_jumps for each index
        // DFS examine: O(n * d) -> each position will be examined at most once
        vector<int> max_jumps(arr.size(), 0);
        for (int i = 0; i < arr.size(); ++i) {
            examine(max_jumps, arr, i, d);
        }
        return *max_element(max_jumps.begin(), max_jumps.end());
    }

private:
    void examine(vector<int>& max_jumps, vector<int>& arr, int i, int d) {
        if (max_jumps[i] != 0) return; // examined!
        bool isEnd = true;
        // go right
        for (int dist = 1; dist <= d && i + dist < arr.size(); ++dist) {
            if (arr[i + dist] >= arr[i]) break;
            isEnd = false;
            examine(max_jumps, arr, i + dist, d);
            max_jumps[i] = max(max_jumps[i], max_jumps[i + dist] + 1);
        }

        // go left
        for (int dist = 1; dist <= d && i - dist >= 0; ++dist) {
            if (arr[i - dist] >= arr[i]) break;
            isEnd = false;
            examine(max_jumps, arr, i - dist, d);
            max_jumps[i] = max(max_jumps[i], max_jumps[i - dist] + 1);
        }

        if (isEnd) max_jumps[i] = 1;
    }
};

struct Pos {
    int max_jumps;
    vector<int> next_list;
    Pos() : max_jumps(0) {}
    Pos(int d) : max_jumps(0) { next_list.reserve(d); }
};

class SolutionSlow {
public:
    // max distance: d
    // cannot pass barrier higher than starting point
    int maxJumps(vector<int>& arr, int d) {
        // Generate a hash map listing all possible positions, max jumps (if examined)
        // Started from positions that cannot be jumped to
        // End with positions cannot jump to anywhere
        // Generate hash map: O(n * d)
        // DFS examine: O(n) -> each position will be examined at most once

        vector<Pos> map(arr.size(), Pos(d)); 
                // don't need to use unordered_map, because keys are indices
        // Generate map
        for (int i = 0; i < arr.size(); ++i) {
            // jump toward right
            for (int dist = 1; dist <= d && i + dist < arr.size(); ++dist) {
                if (arr[i + dist] >= arr[i]) break;
                map[i].next_list.push_back(i + dist);
            }
            // jump toward left
            for (int dist = 1; dist <= d && i - dist >= 0; ++dist) {
                if (arr[i - dist] >= arr[i]) break;
                map[i].next_list.push_back(i - dist);
            }

            if (map[i].next_list.empty()) map[i].max_jumps = 1;
        }

        // Examine each position
        for (int i = 0; i < map.size(); ++i) {
            examinePositions(map, i);
        }

        int ans = 0;
        for (int i = 0; i < map.size(); ++i) {
            ans = max(ans, map[i].max_jumps);
        }
        return ans;
    }

private:
    void examinePositions(vector<Pos>& map, int i) {
        Pos& cur = map[i];
        if (cur.max_jumps > 0) return; // examined
        // DFS
        for (int next : cur.next_list) {
            examinePositions(map, next);
            cur.max_jumps = max(cur.max_jumps, map[next].max_jumps + 1); 
        }
    }
};

int main() {
  Solution demo;
  vector<int> arr {6,4,14,6,8,13,9,7,10,6,12};
  std::cout << demo.maxJumps(arr, 2) << "\n";
}
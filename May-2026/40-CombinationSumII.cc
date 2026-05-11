#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, const int target) {
        // DFS
        vector<vector<int>> paths;
        auto& actions = candidates;
        sort(actions.begin(), actions.end());

        vector<int> path;
        path.reserve(actions.size());
        int sum = 0;

        forward(0, actions, sum, target, path, paths);

        return paths;
    }

private:
    void forward(int current, const vector<int>& actions, int& sum, const int target, 
                vector<int>& path, vector<vector<int>>& paths) {
        if (current >= actions.size()) {
            return;
        }

        bool first = true;
        if (current != 0 && actions[current] == actions[current - 1] && actions[current] != path.back())
            first = false;
        
        while ( current < actions.size() ) {
            sum += actions[current];
            path.push_back(actions[current]);
            if (sum < target) {
                forward(current + 1, actions, sum, target, path, paths);
            } else if (sum == target) {
                paths.push_back(path);
                backward(path, sum);
                break;
            } else {
                backward(path, sum);
                break;
            }
            backward(path, sum);

            current++;
            if (first) {
                while (current < actions.size() && actions[current] == actions[current - 1]) current++;
            } 
        }
        return;
    }

    inline void backward(vector<int>& path, int& sum) {
        sum -= path.back();
        path.pop_back();
    }
};
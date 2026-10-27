#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> ans;
        ans.reserve(m);

        ans.emplace_back(n, '.');
        string s = string(n-1, '#')+'.';
        for (int _ = 1; _ < m; ++_) {
            ans.push_back(s);
        }
        return ans;
    }
};
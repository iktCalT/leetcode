#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // DFS
        vector<string> ans;
        string str = "(";
        int lcnt = n - 1;
        int rcnt = n;
        int diff = 1;

        dfs(str, lcnt, rcnt, diff, ans);

        return ans;
    }

private:
    void dfs(string& str, int& lcnt, int& rcnt, int& diff, vector<string>& ans) {
        if (rcnt == 0) {
            ans.push_back(str);
            return;
        }

        // add '('
        if (lcnt > 0) {
            str += '(';
            --lcnt;
            ++diff;
            dfs(str, lcnt, rcnt, diff, ans);

            // recover
            str.pop_back();
            ++lcnt;
            --diff;
        }

        // add ')'
        if (diff > 0 && rcnt > 0) {
            str += ')';
            --rcnt;
            --diff;
            dfs(str, lcnt, rcnt, diff, ans);

            // recover
            str.pop_back();
            ++rcnt;
            ++diff;
        }
    }
};
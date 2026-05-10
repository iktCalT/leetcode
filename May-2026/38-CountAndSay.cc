#include <string>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        // use iteration rather than recursion
        string ans = "1";
        for(int i = 1; i < n; i++) {
            ans = nextStep(ans);
        }
        return ans;
    }
private:
    string nextStep(const string& s) {
        string next;
        int count = 0;
        for (int i = 0; i < s.size(); i++) {
            count++;
            if (i == s.size() - 1 || s[i + 1] != s[i]) {
                // end of contiguous number
                next += to_string(count);
                next += s[i];
                count = 0;
            }
        }
        return next;
    }
};
#include <climits>
#include <string>

using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int ans = 0;
        int i = 0; // index
        // sign
        int sign = 1;
        for ( ; i < s.size(); i++) {
            if (s[i] == ' ') {
                continue;
            } else if (s[i] == '+') {
                i++;
                break;
            } else if (s[i] == '-') {
                sign = -1;
                i++;
                break;
            } else if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
                break;
            } else {
                return 0;
            }
        }

        // number
        for ( ; i < s.size(); i++) {
            if (s[i] - '0' < 0 || s[i] - '0' > 9) {
                break;
            }

            bool overflow = sign > 0 
                    ? (ans > INT_MAX / 10 || s[i] - '0' > INT_MAX - 10 * ans) 
                    : (ans < INT_MIN / 10 || -(s[i] - '0') < INT_MIN - 10 * ans);
            if (overflow) { // notice that (INT_MAX / 10 == INT_MIN / 10)
                return sign > 0 ? INT_MAX : INT_MIN;
            }
            ans = sign * (s[i] - '0') + ans * 10; 
                    // be careful, if we use (ans * 10 + s[i] - '0'), 
                    // there may be overflow while calculating (ans * 10 + s[i])
        }
        return ans;
    }
};
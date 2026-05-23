#include <string>

class Solution {
public:
    int lengthOfLastWord(std::string s) {
        auto crit = s.crbegin();
        for ( ; crit != s.crend(); ++crit) {
            if (*crit != ' ') break;
        }

        auto rpos = crit;
        for ( ; crit != s.crend(); ++crit) {
            if (*crit == ' ') break;
        }

        return distance(rpos, crit);
    }
};
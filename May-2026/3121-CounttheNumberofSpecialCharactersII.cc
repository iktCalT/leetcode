#include <string>
#include <array>

class Solution {
public:
    int numberOfSpecialChars(std::string word) {
        // 0: haven't occurred, 1: only lowercase, 
        // 2: lower & upper and lower before upper, 3: lower and upper but lower after upper
        constexpr int num_letters = 26;
        int cnt = 0;
        std::array<int, num_letters> alphabet;

        for (const char& c : word) {
            bool is_lower = true;
            char pos= c - 'a';
            if (pos < 0 || pos > num_letters) { // only pos < 0 is possible 
                is_lower = false;
                pos = c - 'A';
            }

            switch (alphabet[pos]) {
            case 3:
                break;
            case 2:
                if (!is_lower) break;
                // If lower
                alphabet[pos] = 3;
                --cnt;
                break;
            case 1:
                if (is_lower) break;
                // If upper
                alphabet[pos] = 2;
                ++cnt;
                break;
            default: // case 0:
                if (is_lower) {
                    alphabet[pos] = 1;
                } else {
                    alphabet[pos] = 3;
                }
            }
        }

        return cnt;
    }
};
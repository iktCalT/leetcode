#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        vector<char> ONES = {'I', 'X', 'C', 'M'};
        vector<char> FIVES = {'V', 'L', 'D'};
        int result = 0;
        int last_c = 0;
        int this_c = 0;
        bool is_ones = false;

        for (size_t i = 0; i < s.length(); i++, last_c = this_c, this_c = 0) {
            // Match roman letters
            for (size_t j = 0; j < FIVES.size() + ONES.size(); j++) {
                if (j < FIVES.size()) {
                    if (s[i] == FIVES[j]) 
                        this_c = 5 * pow(10, j);
                    else 
                        continue;
                } else if (j >= FIVES.size()) {
                    if (s[i] == ONES[j - FIVES.size()]) {
                        this_c = 1 * pow(10, j - FIVES.size());
                        is_ones = true;
                    } 
                    else
                        continue;
                }
            }

            if (this_c == 0)
                throw runtime_error("Undefined letters");

            result += this_c;

            if (is_ones && (last_c == this_c / 5 || last_c == this_c / 10)) {
                result -= 2 * last_c;
            }
        }

        return result;
    }
};

int main() {
    Solution demo = Solution();
    printf("%d\n", demo.romanToInt("III"));     // 3
    printf("%d\n", demo.romanToInt("IV"));      // 4
    printf("%d\n", demo.romanToInt("LVIII"));   // 58
    printf("%d\n", demo.romanToInt("MCMXCIV")); // 1994
}
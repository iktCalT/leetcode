#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<vector<char>> letters = {
            {'a', 'b', 'c'}, // 2
            {'d', 'e', 'f'}, 
            {'g', 'h', 'i'}, 
            {'j', 'k', 'l'}, 
            {'m', 'n', 'o'}, 
            {'p', 'q', 'r', 's'}, 
            {'t', 'u', 'v'}, 
            {'w', 'x', 'y', 'z'}};
        vector<string> combinations;
        combinations.reserve(pow(3, digits.size())); // at least 3 ^ n

        for (char c : letters[digits[0] - '0' - 2]) {
            combinations.push_back(string(1, c));
        }

        for (int idigits = 1; idigits < digits.size(); idigits++) {
            // combination's size will change, so we need to record it
            int curSize = combinations.size(); 
            auto& tmp_letters = letters[digits[idigits] - '0' - 2];

            for (int iletters = 1; iletters < tmp_letters.size(); iletters++) {
                for (int icom = 0; icom < curSize; icom++) {
                    combinations.emplace_back(
                            combinations[icom] + tmp_letters[iletters]);
                }
            }

            for (int icom = 0; icom < curSize; icom++) {
                combinations[icom] += letters[digits[idigits] - '0' - 2][0];
            }
        }

        return combinations;
    }
};
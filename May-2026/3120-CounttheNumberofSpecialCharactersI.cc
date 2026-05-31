#include <string>
#include <unordered_map>
#include <array>

using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        int count = 0;
        array<int, 26> map; // filled with 0
        for (char c : word) {
            bool is_lower = false;
            if (c - 'a' >= 0 && c - 'z' <= 0) is_lower = true;

            int pos = is_lower ? c - 'a' : c - 'A';
            if (map[pos] == 0) {
                map[pos] = is_lower + 1;
            } else if (map[pos] == 1 + !is_lower) {
                map[pos] = 3;
                ++count;
            }
        }

        return count;
    }
};

class SolutionSlow {
public:
    int numberOfSpecialChars(string word) {
        int count = 0;
        // map: key: English letter in lowercase; value: 0: only uppercase, 1: only lowercase, 2: paired
        unordered_map<char, int> map;

        for (char c : word) {
            int is_lower = false;
            if (c - 'a' >= 0 && c - 'z' <= 0) is_lower = true;
            if (!is_lower) c = c - 'A' + 'a'; // to lower

            if (map.find(c) == map.end()) {
                // not in map
                map.insert({c, is_lower});
                continue;
            }

            // in map
            if (map[c] == !is_lower) {
                ++count;
                map[c] = 2;
            }
        }

        return count;
    }
};
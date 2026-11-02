#include <cstdint>
#include <string>
#include <vector>
#include <ranges>

using namespace std;

class Solution {
public:
  int maxProduct(vector<string>& words) {
    // bit manipulation
    // Use a u32 to represent the exsitance of letters
    int n = words.size();
    vector<uint32_t> letters(n, 0);
    for (const auto& [i, s] : views::enumerate(words)) {
      for (const char& c : s) {
        letters[i] |= 1 << (c - 'a');
      }
    }

    unsigned long longest = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if ((letters[i] & letters[j]) == 0) {
          longest = max(longest, words[i].size() * words[j].size());
        }
      }
    }

    return longest;
  }
};
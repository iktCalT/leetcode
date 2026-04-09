#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  std::string longestCommonPrefix(std::vector<std::string> &strs) {
    if (strs.size() == 0) {
      return "";
    }

    size_t lcp_length = strs[0].length(); // length of longest common prefix
    for (int _ = 1; _ < strs.size(); _++) {
       lcp_length = lcpLength(strs[0], strs[_], lcp_length);
    }
    return strs[0].substr(0, lcp_length);
  }

private:
  size_t lcpLength(std::string &str0, std::string &str, size_t lcp_length) {
    // Usually, lcp < strs[i], so we loop through lcp
    // Pass by reference is faster. str0.substr(0, length) is current longest
    // common prefix
    size_t new_length = 0;
    for (; new_length < lcp_length; new_length++) {
      if (str0[new_length] != str[new_length])
        break;
    }
    return new_length;
  }
};

int main() {
  Solution demo = Solution();
  std::vector<std::string> strs = {"flower", "flow", "flight"};
  std::cout << demo.longestCommonPrefix(strs) << std::endl;

  strs = {"dog", "racecar", "car"};
  std::cout << demo.longestCommonPrefix(strs) << std::endl;

  strs = {"dog"};
  std::cout << demo.longestCommonPrefix(strs) << std::endl;

  strs = {};
  std::cout << demo.longestCommonPrefix(strs) << std::endl;
}
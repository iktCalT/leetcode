#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  std::string convert(std::string s, int numRows) {
    if (numRows == 1) {
      return s;
    }
    std::vector<std::string> pattern(numRows);
    int goingDown = true;
    int row = 0;
    for (char c : s) {
      pattern[row] += c;
      row += goingDown ? 1 : -1;
      if (row == 0 || row == numRows - 1) {
        goingDown = !goingDown;
      }
    }
    std::string result;
    for (auto str : pattern) {
      result += str;
    }
    return result;
  }
};

class SolutionAna {
public:
  std::string convert(std::string s, int numRows) {
    if (numRows == 1) {
      return s;
    }
    int loop = 2 * numRows - 2;
    std::string result;
    for (int row = 0; row <= numRows; row++) {
      for (int times = 0; times * loop < s.length(); times++) {
        if (loop * times + row < s.length())
          result += s[loop * times - row];
        if (row == 0 || row == numRows - 1)
          continue;
        if (loop * (times + 1) - row < s.length())
          result += s[loop * times + row];
      }
    }
    return result;
  }
};

class SolutionSlow {
public:
  std::string convert(std::string s, int numRows) {
    if (numRows == 1) {
      return s;
    }
    std::vector<std::vector<char>> pattern(numRows);
    for (int i = 0; i < s.length(); i++) {
      int ri = i % (2 * numRows - 2);                     // ri: relative index
      int row = ri < numRows ? ri : 2 * numRows - 2 - ri; // row number
      pattern[row].push_back(s[i]);
    }
    return vec2Str(pattern);
  }

private:
  std::string vec2Str(const std::vector<std::vector<char>> &pattern) {
    std::string result;
    for (auto row : pattern) {
      if (row.size() == 0)
        break;
      result += std::string{row.begin(), row.end()};
    }
    return result;
  }
};

int main() {
  Solution demo;
  std::cout << demo.convert("PAYPALISHIRING", 3) << std::endl;
  std::cout << demo.convert("PAYPALISHIRING", 100) << std::endl;
  std::cout << demo.convert("AB", 2) << std::endl;
}
#include <string>

class Solution {
public:
  int minAddToMakeValid(std::string s) {
    // Iteratre from left to right
    // Eache step, #'(' >= #')'
    // Last step, #'(' == #')'

    int moves = 0;
    int net = 0;
    for (const char c : s) {
      switch (c) {
      case '(':
        ++net;
        break;
      default:
        bool exceed = net == 0;
        net -= 1 - exceed;
        moves += exceed;
      }
    }

    return moves + net;
  }
};
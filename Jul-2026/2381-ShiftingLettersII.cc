#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  string shiftingLetters(string s, vector<vector<int>>& shifts) {
    // A reverse version of **prefix sum**
    // Let's assume shift[i + 1] is the shift for index i
    // shift[0] is always 0
    // Let's record the difference between shift[i] 
    // and shift[i - 1] in shift_diff[i]
    const int n = s.size();
    vector<int> shift_diff(n + 1, 0);

    for (const vector<int>& s : shifts) {
      int dir = (s[2] * 2) - 1;
      shift_diff[s[0]] += dir;
      shift_diff[s[1] + 1] -= dir;
    }

    int shift = 0;
    for (int i = 0; i < n; ++i) {
      shift += shift_diff[i];
      s[i] = shiftChar(s[i], shift);
    }

    return s;
  }

private:
  inline char shiftChar(const char c, int shift) {
    shift = shift % 26; // -25 to 25
    return ((c - 'a' + shift + 26) % 26) + 'a';
  }
};
#include <string>
class Solution {
public:
  int maxProduct(int n) {
    // 10 <= n <= 10^9
    std::string str = std::to_string(n);
    char fst = '0';
    char scn = '0';
    for (char c : str) {
      if (c > fst) {
        scn = fst;
        fst = c;
      } else if (c > scn) {
        scn = c;
      }
    }

    return (int)(fst - '0') * (scn - '0');
  }
};
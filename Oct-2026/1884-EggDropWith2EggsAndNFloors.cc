class Solution {
public:
  int twoEggDrop(int n) {
    // n -> n-1 -> n-1-2 -> n-1-2-3 -> n-1-2-3-4 -> ...
    // n - 1 - ... - x <= 0 
    // x(x+1)/2 >= n
    // x^2 + x >= 2n
    int i = 0;
    while (true) {
      if (i*(i+1) >= 2 * n) return i;
      ++i;
    }
  }
};
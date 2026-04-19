#include <cstdlib>
#include <iostream>

class Solution {
public:
  int mirrorDistance(int n) { return std::abs(n - reverseInteger(n)); }

private:
  int reverseInteger(int n) {
    int reversed = 0;
    while (n != 0) {
      reversed = reversed * 10 + n % 10;
      n /= 10;
    }
    return reversed;
  }
};

int main() {
  Solution demo;
  std::cout << demo.mirrorDistance(10) << std::endl;
  std::cout << demo.mirrorDistance(99) << std::endl;
  std::cout << demo.mirrorDistance(12) << std::endl;
  std::cout << demo.mirrorDistance(9) << std::endl;
}
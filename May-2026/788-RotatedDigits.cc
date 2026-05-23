#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#define VALID_DIGITS 7
#define VALID_UNCHANGE_DIGITS 3

struct Digit {
  int type;
  int change;
  int unchange;

  Digit(int type, int change, int unchange)
      : type(type), change(change), unchange(unchange) {}
};

class SolutionAnalytical {
public:
  int rotatedDigits(int n) {
    // e.g. n = 123 -> vec: {1,2,3}
    // 1st round: 1 to 99 (equivalent to 0 to 99)
    // 2nd round: 100 to 119
    // 3rd round: 120 to 123

    // Note that if n = 321
    // 1st round: 1 to 299
    // No 2nd/3rd round, because rotate 3 is invalid
    int count = 0;
    auto vec = int2Vector(n);
    bool isChange = false;
    for (int i = 0; i < vec.size(); i++) {
      auto parsed = parseDigit(vec[i]);
      if (i == vec.size() - 1) {
        count += parsed.change + parsed.unchange * isChange;
        break;
      }

      if (parsed.type == 2) { // change
        count += (parsed.change + parsed.unchange - 1) *
                 pow(VALID_DIGITS, vec.size() - i - 1);
        if (!isChange) {
          count -=
              parsed.unchange * pow(VALID_UNCHANGE_DIGITS, vec.size() - i - 1);
        }
        isChange = true;
      } else if (parsed.type == 1) { // unchange
        count += (parsed.change + parsed.unchange - 1) *
                 pow(VALID_DIGITS, vec.size() - i - 1);
        if (!isChange) {
          count -= (parsed.unchange - 1) *
                   pow(VALID_UNCHANGE_DIGITS, vec.size() - i - 1);
        }
      } else { // invalid
        count += (parsed.change + parsed.unchange) *
                 pow(VALID_DIGITS, vec.size() - i - 1);
        if (!isChange) {
          count -=
              parsed.unchange * pow(VALID_UNCHANGE_DIGITS, vec.size() - i - 1);
        }
        break;
      }
    }
    return count;
  }

private:
  inline Digit parseDigit(int d) {
    int type, change = 0, unchange = 0;
    switch (d) {
    case 9:
      change++;
    case 8:
      unchange++;
    case 7:
    case 6:
      change++;
    case 5:
      change++;
    case 4:
    case 3:
    case 2:
      change++;
    case 1:
      unchange++;
    case 0:
      unchange++;
    }
    switch (d) {
    case 0:
    case 1:
    case 8:
      type = 1;
      break;
    case 2:
    case 5:
    case 6:
    case 9:
      type = 2;
      break;
    default:
      type = 0;
    }
    return {type, change, unchange};
  }

  inline std::vector<int> int2Vector(int n) {
    std::vector<int> vec;
    while (n != 0) {
      vec.insert(vec.begin(), n % 10);
      n /= 10;
    }
    return vec;
  }
};

class SolutionLoopFast {
  // copied from others' answer
private:
  bool isGoodNo(int n) {
    bool hasDiffDigit = false;

    while (n > 0) {
      int digit = n % 10;

      // 1. If it contains 3, 4, or 7, it's immediately invalid
      if (digit == 3 || digit == 4 || digit == 7) {
        return false;
      }

      // 2. If it contains 2, 5, 6, or 9, it will definitely change the number's
      // value
      if (digit == 2 || digit == 5 || digit == 6 || digit == 9) {
        hasDiffDigit = true;
      }

      n /= 10;
    }

    // It's good only if it had no invalid digits AND at least one digit changed
    return hasDiffDigit;
  }

public:
  int rotatedDigits(int n) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (isGoodNo(i))
        cnt++;
    }
    return cnt;
  }
};

class SolutionLoopSlow {
public:
  int rotatedDigits(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
      count += isGoodInteger(i);
    }
    return count;
  }

private:
  std::vector<int> intToDigits(int n) {
    std::vector<int> digits;
    while (n != 0) {
      digits.insert(digits.begin(), n % 10);
      n /= 10;
    }
    return digits;
  }

  inline int rotation(int a) {
    // return 0 if invalid; return 1 if valid but unchanged;
    // return 2 if valid and changed
    if (a < 0 || a > 9) {
      throw std::runtime_error("isRotate: invalid argument");
    }
    switch (a) {
    case 0:
    case 1:
    case 8:
      return 1;
      break;
    case 2:
    case 5:
    case 6:
    case 9:
      return 2;
      break;
    default:
      return 0;
    }
  }

  bool isGoodInteger(int n) {
    auto digits = intToDigits(n);
    bool changed = false;
    for (auto &digit : digits) {
      switch (rotation(digit)) {
      case 0:
        return 0;
      case 2:
        changed = true;
      }
    }
    return changed;
  }
};

int main() {
  SolutionAnalytical demo;
  std::cout << demo.rotatedDigits(857) - 247 << std::endl;
  std::cout << demo.rotatedDigits(10) - 4 << std::endl;
  std::cout << demo.rotatedDigits(7) - 3 << std::endl;
  std::cout << demo.rotatedDigits(10000) - 2320 << std::endl;
  std::cout << demo.rotatedDigits(516) - 141 << std::endl;
  std::cout << demo.rotatedDigits(7894) - 1661 << std::endl;
  std::cout << demo.rotatedDigits(312) - 129 << std::endl;
  std::cout << demo.rotatedDigits(436) - 129 << std::endl;
  std::cout << demo.rotatedDigits(400) - 129 << std::endl;
}
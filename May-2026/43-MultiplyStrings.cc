#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";

        vector<int> result(num1.size() + num2.size(), 0);

        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int outer = 0;
        for (int i = 0; i < num1.size(); ++i) {
            for (int j = 0; j < num2.size(); ++j) {
                result[i + j] += (num1[i] - '0') * (num2[j] - '0'); // could be larger than 10
            }
        }

        int end = result.size() - 1;
        for (; end >= 0; --end) {
            if (result[end] != 0) break;
        }

        string ans = "";
        int carry = 0;
        for (int i = 0; i <= end; i++) {
            ans = (char)((result[i] + carry) % 10 + '0') + ans;
            carry = (result[i] + carry) / 10;
        }

        if (carry) {
            ans = to_string(carry) + ans;
        }

        return ans;
    }
};

class SolutionSlow {
public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
      return "0";
    }

    // num1 should be longer
    if (num1.size() < num2.size()) {
      return multiply(num2, num1);
    }

    string ans = "0";
    string times = "";
    for (auto crit1 = num1.crbegin(); crit1 != num1.crend(); ++crit1) {
      ans = addition(ans, onesMultiplyWhole(*crit1, num2) + times);
      times += '0';
    }
    return ans;
  }

private:
  inline string onesMultiply(char ones1, char ones2) {
    int result = (ones1 - '0') * (ones2 - '0');
    return to_string(result);
  }

  string addition(string num1, string num2) {
    // make sure num1 is shorter
    if (num2.size() > num1.size()) {
      return addition(num2, num1);
    }

    string result;
    int carry = 0;
    int i = 0;
    for (; i < min(num1.size(), num2.size()); ++i) {
      int addition = (num1[num1.size() - 1 - i] - '0') +
                     (num2[num2.size() - 1 - i] - '0') + carry;
      carry = addition / 10;
      result = (char)((addition % 10) + '0') + result;
    }

    for (; i < num1.size(); ++i) {
      if (carry == 0) {
        result.insert(result.begin(), num1.begin(), num1.end() - i);
        return result;
      }

      int addition = (num1[num1.size() - 1 - i] - '0') + carry;
      carry = addition / 10;
      result = (char)((addition % 10) + '0') + result;
    }

    if (carry != 0) {
      result = (char)(carry + '0') + result;
    }

    return result;
  }

  unordered_map<char, string> checkTable;

  string onesMultiplyWhole(char ones, const string& num) {
    auto it = checkTable.find(ones);
    if (it != checkTable.end()) {
      return it->second;
    }

    string ans = "0";
    string times = "";
    for (auto crit = num.crbegin(); crit != num.crend(); ++crit) {
      ans =
          addition(ans, onesMultiply(ones, *crit) + times);
      times += '0';
    }
    checkTable.insert({ones, ans});
    return ans;
  }
};

int main() {
  Solution demo;
  std::cout << demo.multiply("123", "456") << std::endl;
}
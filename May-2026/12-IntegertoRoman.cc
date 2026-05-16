#include <iostream>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        string roman;

        int thousands = num / 1000;
        if (thousands > 3) throw runtime_error("Too large!");
        parseDigit(roman, thousands, 'M', ' ', ' ');
        num -= 1000 * thousands;

        int hundreds = num / 100;
        parseDigit(roman, hundreds, 'C', 'D', 'M');
        num -= 100 * hundreds;

        int tens = num / 10;
        parseDigit(roman, tens, 'X', 'L','C');
        num -= 10 * tens;

        int ones = num;
        parseDigit(roman, ones, 'I', 'V', 'X');

        return roman;
    }

private:
    inline void parseDigit(string& roman, int digit, char one, char five, char ten) {
        switch(digit) {
        case 9:
            roman = roman + one + ten;
            break;
        case 8:
            roman = roman + five + one + one + one;
            break;
        case 7:
            roman = roman + five + one + one;
            break;
        case 6:
            roman = roman + five + one;
            break;
        case 5:
            roman = roman + five;
            break;
        case 4:
            roman = roman + one + five;
            break;
        case 3:
            roman = roman + one;
        case 2:
            roman = roman + one;
        case 1:
            roman = roman + one;
        case 0:
            break;
        default:
            throw runtime_error("Error!");
        }
    }
};

int main() {
  Solution demo;
  std::cout << demo.intToRoman(1234) << std::endl;
}
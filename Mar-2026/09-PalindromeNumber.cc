#include <iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        string sx = to_string(x);
        for (size_t i = 0; i < sx.size(); i++) {
            if (sx[i] != sx[sx.size() - 1 - i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution demo = Solution();
    printf("%b\n", demo.isPalindrome(12321));
    printf("%b\n", demo.isPalindrome(-121));
    printf("%b\n", demo.isPalindrome(0));
}
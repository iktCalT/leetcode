#include <csignal>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    /*
     Similar to Question "Longest Substring Without Repeating Characters",
     when we add a character to the end of a string, the longest palindromic
     substring is either the longest palindromic substring of the original
     one, or the one with the new character.

     More importantly,
     Case 1: if the new palindromic substring (the one with new
     character, let's call it current_pld) is longer than the old one (let' call
     it longest_pld), then the center of current_pld must be the center of
     (longest_pld);  current_pld could add 2 (abcb -> abcba) or 1 (aaa ->
     aaaa).

     Case 2: if they are the same size, they may merge and become a new
     larger pld (for example: "abcbaxabcb" + 'a', where the longest_pld is
     "abcba", and the current_pld turns form "bcb" to "abcba". They will merge
     and become "abcbaxabcba"). Let's call the "bcb" above end_pld. If they
     can merge, renew the largest size and longest_pld.

     Case 3: Else (same size, no merge), set the current_pld as longest_pld.

     Case 4: current_pld is shorter than longest_pld

     Actually, case 2 won't happen. in the example above longest_pld is
     "bcbaxabcb".

     So, to find out the current_pld, we just need to look the previous
     longest_pld.length() - 1 characters before the new one, if they are
     new_character + end_pld (end_pld.length() = longest_pld.length()).
     It means that we don't need to check the whole old string to find out
     current_pld. Moreover the first case (current_pld and longest_pld have same
     center) is equivalent to (longest_pld is end_pld).

     Note that end_pld is actually the last current_pld.

     In conclusion, there are only 3 possible cases -- "current_pld longer than
     longest_pld", "they are the same size", and "current_pld is shorter than
     longest_pld". In the first 2 cases, we need to set the longest_pld as
     current_pld, but in the last case, we don't need to renew longest_pld
     */

    if (s.length() <= 1) {
      // If s is empty or has only 1 character.
      return s;
    }

    int longest_size = 1; // size of longest_pld
    int start = 0;        // index of the start of longest_pld
    int cur;              // index of current character

    for (cur = 1; cur < s.length(); cur++) {
      if (cur > longest_size && isPld(s, cur - longest_size - 1, cur)) {
        start = cur - longest_size - 1;
        longest_size += 2;
      } else if (cur >= longest_size && isPld(s, cur - longest_size, cur)) {
        start = cur - longest_size;
        longest_size += 1;
      } else if (isPld(s, cur - longest_size + 1, cur)) {
        start = cur - longest_size + 1;
      } else {
        // DO NOTHING
      }
    }

    return s.substr(start, longest_size);
  }

private:
  bool isPld(string &s, int start, int end) {
    // if "xyzabcb" + 'a', the longest_pld: "bcb" -> "abcba", return true
    // start: first a; end: current character (a)

    // Boundary check
    if (start < 0 || start > end || end >= s.length())
      // make sure 0 <= start <= end < size
      // we can compare end (int) with size(size_t) safely
      // because end >= start >= 0
      return false;

    for (int cur = start; cur <= (start + end) / 2; cur++) {
      if (s[cur] != s[end + start - cur]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution demo = Solution();

  // std::cout << demo.longestPalindrome("xyabcdcbazz") << std::endl;
  // std::cout << demo.longestPalindrome("abcxxxxxxxccc") << std::endl;
  std::cout << demo.longestPalindrome("babad") << std::endl;
  std::cout << demo.longestPalindrome("cbbd") << std::endl;
}
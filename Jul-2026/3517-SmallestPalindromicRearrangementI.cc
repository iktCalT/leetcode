#include <array>
#include <algorithm>
#include <string>
using namespace std;

/* 27ms */
class Solution {
public:
  string smallestPalindrome(string s) {
    array<int, 26> cnt;
    int n = s.size();
    for (int i = 0; i < n / 2; ++i) 
      ++cnt[s[i] - 'a'];
    
    char c = 'a';
    int cur = 0;
    for (int k : cnt) {
      for (int i = 0; i < k; ++i) {
        s[cur] = c;
        ++cur;
      }
      ++c;
    }

    for (int i = 0; i < n/2; ++i) {
      s[n - 1 - i] = s[i];
    }
    return s;
  }
};

/* 104ms */
class Solution1 {
public:
  string smallestPalindrome(string s) {
    // sort the first half, and mirror it
    int n = s.size();
    string fst_half{s.begin(), s.begin() + n/2};
    sort(fst_half.begin(), fst_half.end());
    string scn_half = fst_half;
    reverse(scn_half.begin(), scn_half.end());
    if (n % 2) {
      return fst_half + s[n / 2] + scn_half;
    } else {
      return fst_half + scn_half;
    }
  }
};

/* 95ms */
class Solution0 {
public:
  string smallestPalindrome(string s) {
    // sort the first half, and mirror it
    int n = s.size();
    sort(s.begin(), s.begin() + n/2);
    for (int i = 0; i < n/2; ++i) {
      s[n - 1 - i] = s[i];
    }
    return s;
  }
};
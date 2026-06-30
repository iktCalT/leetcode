#include <array>
#include <string>

using namespace std;

class Solution {
public:
  int numberOfSubstrings(string s) {
    // Two pointers
    const int n = s.size();
    s += 'd'; // eliminate edge condition

    // count of 'a', 'b', 'c', 'd' in [l, r)
    array<int, 4> cnt = {0, 0, 0, 0}; 
    int ans = 0;

    int l = 0, r = 0;
    while (l <= n) {
      // Find the first l, making [l, r) doesn't contain 'a', 'b', and 'c'
      while (containAll(cnt)) {
        ans += n - r + 1; // r ranging from r to n
        --cnt[s[l] - 'a'];
        ++l;
      }

      // Find first r, making sure [l, r) contains 'a', 'b', and 'c'
      while (r <= n) {
        // s only consists of a, b or c characters (+ 'd' as ending)
        ++cnt[s[r] - 'a'];
        ++r;
        if (containAll(cnt)) break;
      }

      if (cnt[3]) break; // no subarrays fulfill requirement any more
    }

    return ans;
  }

private:
  inline bool containAll(const array<int, 4>& cnt) { 
    for (int i = 0; i < 3; ++i) {
      if (cnt[i] == 0) return false;
    }
    return true;
  }
};

class Solution0 { // TLE
public:
  int numberOfSubstrings(string s) {
    const int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      array<int, 3> cnt = {0, 0, 0};
      for (int j = i; j < n; ++j) {
        if (int pos = s[j] - 'a'; pos < 3) {
          ++cnt[pos];
          if (containAll(cnt)) {
            // start: i
            // end: from j to s.size() - 1
            ans += n - j;
            break;
          }
        }
      }
    }
    return ans;
  }

private:
  bool containAll(const array<int, 3> cnt) { // copying should be faster
    for (int c : cnt) {
      if (c <= 0) return false;
    }
    return true;
  }
};
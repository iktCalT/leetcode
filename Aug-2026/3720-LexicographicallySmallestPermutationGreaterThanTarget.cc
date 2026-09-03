#include <algorithm>
#include <array>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
  string lexGreaterPermutation(string s, string target) {
    // Gather information from s, the order of letters 
    // in s doesn't matter. Only count matters
    array<int, 26> cnt;
    fill(cnt.begin(), cnt.end(), 0);
    int n = s.size(); // s.size() == target.size() == n

    for (const char& c : s) {
      ++cnt[c - 'a'];
    }

    // Find the answer
    int iters = 0;

    for (const char c : target) {
      if (cnt[c - 'a'] != 0) {
        --cnt[c - 'a'];
        ++iters;
        continue;
      }

      int next_pos = nextPos(cnt, c - 'a');
      if (next_pos == -1) break;

      --cnt[next_pos];
      string ans = string(target.begin(), target.begin() + iters);
      ans.reserve(n);
      ans.push_back('a' + next_pos);
      for (int i = 0; i < 26; ++i) {
        ans += string(cnt[i], 'a' + i);
      }
      return ans;
    }

    // s and target are consist of same set of letters
    for (int i = iters - 1; i >= 0; --i) {
      ++cnt[target[i] - 'a'];
      --iters;

      int next_pos = nextPos(cnt, target[i] - 'a');
      if (next_pos != -1) {
        string ans = string(target.begin(), target.begin() + iters);
        ans.reserve(n);
        ans.push_back('a' + next_pos);
        --cnt[next_pos];
        for (int i = 0; i < 26; ++i) {
          ans += string(cnt[i], 'a' + i);
        }
        return ans;
      }
    }

    return ""; 
  }

private:
  int nextPos(array<int, 26>& cnt, int pos) {
    // Find the position i > pos where cnt[i] != 0
    // return -1 if doesn't

    if (pos < 0 || pos >= 26) throw runtime_error("Bug!");

    for (int i = pos + 1; i < 26; ++i) {
      if (cnt[i] != 0) return i;
    }
    return -1;
  }
};

int main() {
  Solution demo;
  std::cout << demo.lexGreaterPermutation("aab", "abb") << "\n";
}
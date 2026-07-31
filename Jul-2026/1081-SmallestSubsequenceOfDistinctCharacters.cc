#include <algorithm>
#include <array>
#include <string>
using namespace std;


/* Really hard */
class Solution {
public:
  string smallestSubsequence(string s) {
    array<bool, 26> vis;
    fill(vis.begin(), vis.end(), false);
    array<int, 26> cnt;
    fill(cnt.begin(), cnt.end(), 0);

    for (char c : s) {
      ++cnt[c - 'a'];
    }
    
    string ans;
    for (char c : s) {
      if (vis[c - 'a']) {
        --cnt[c - 'a'];
        continue;
      }

      while (!ans.empty() && c < ans.back()) {
        if (cnt[ans.back() - 'a'] > 0) {
          vis[ans.back() - 'a'] = false;
          ans.pop_back();
        } else {
          break;
        }
      }

      ans = ans + c;
      --cnt[c - 'a'];
      vis[c - 'a'] = true;
    }

    return ans;
  }
};
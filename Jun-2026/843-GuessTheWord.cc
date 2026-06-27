#include <string>
#include <vector>
using namespace std;

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */

class Master {
  public:
    int guess(string word);
};

class Solution {
public:
  void findSecretWord(vector<string>& words, Master& master) {
    while (true) {
      string cur = words[0];
      fastErase(words.begin(), words);

      int cnt = master.guess(cur);
      if (cnt == 6) break;
      for (auto it = words.begin(); it != words.end(); ++it) {
        if (match(cur, *it) != cnt) {
          fastErase(it, words);
          --it;
        }
      }
    }
  }

private:
  int match(const string& a, const string& b) {
    int ans = 0;
    for (int i = 0; i < 6; ++i) {
      if (a[i] == b[i]) ++ans;
    }
    return ans;
  }

  void fastErase(vector<string>::iterator it, vector<string>& words) {
    *it = words.back();
    words.pop_back();
  }
};
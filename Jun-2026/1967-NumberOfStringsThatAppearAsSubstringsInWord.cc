#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  int numOfStrings(vector<string>& patterns, string word) {
    array<vector<int>, 26> poss; // positions
    for (int i = 0; i < word.size(); ++i) {
      poss[word[i] - 'a'].push_back(i);
    }
    int cnt = 0;
    for (const string& pat : patterns) {
      for (int pos : poss[pat[0] - 'a']) {
        if (exists(pos, pat, word)) {
          ++cnt;
          break;
        }
      }
    }
    return cnt;
  }

private:
  bool exists(int pos, const string& pat, const string& word) {
    if (pat.size() + pos > word.size()) return false;
    for (int i = 0; i < pat.size(); ++i) {
      if (pat[i] != word[pos + i]) return false;
    }
    return true;
  }
};
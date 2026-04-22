#include <string>
#include <vector>
using namespace std;
// finished directly on leetcode

class Solution {
public:
  vector<string> twoEditWords(vector<string> &queries,
                              vector<string> &dictionary) {
    vector<string> results;
    for (auto src : queries) {
      for (auto dest : dictionary) {
        if (HammingDistance(src, dest) <= 2) {
          results.insert(results.end(), src);
          break;
        }
      }
    }
    return results;
  }

private:
  int HammingDistance(string &word1, string &word2) {
    int hammingDistance =
        max(word1.size(), word2.size()) - min(word1.size(), word2.size());
    for (int i = 0; i < min(word1.size(), word2.size()); i++) {
      if (word1[i] != word2[i]) {
        hammingDistance++;
      }
    }
    return hammingDistance;
  }
};
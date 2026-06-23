#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string mapWordWeights(vector<string>& words, vector<int>& weights) {
    string ans;
    ans.reserve(words.size());
    for (const string& word : words) {
      ans.push_back('z' - getWeight(word, weights));
    }
    return ans;
  }

private:
  inline char getWeight(const string& word, const vector<int>& weights) {
    int w = 0;
    for (char c : word) {
      w += weights[c - 'a'];
    }
    return w % 26; // implicit conversion: int to char
  }
};
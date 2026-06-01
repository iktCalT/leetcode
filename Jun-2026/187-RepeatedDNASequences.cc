
#include <array>
#include <functional>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution { // 40 ms Beats 62.26%
public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> ans;
    if (s.size() <= 10) return ans;

    // Trie
    unordered_map<string_view, int> cnt;
        // With less<>, I can find string_views in this ordered map
    for (int i = 0; i + 9 < s.size(); ++i) {
      string_view str(s.c_str() + i, 10);
      auto it = cnt.find(str);
      if (it != cnt.end()) {
        ++it->second;
        if (it->second == 2) {
          ans.push_back(string(str.data(), str.size()));
        }
      } else {
        cnt.insert({str, 1});
      }
    }
    return ans;
  }
};

class SolutionTrie { // 59 ms Beats 16.53%
public:
  vector<string> findRepeatedDnaSequences(string s) {
    if (s.size() <= 10) return vector<string>();

    // Trie
    set<string, less<>> ans; 
        // With less<>, I can find string_views in this set
    TrieNode* const root = new TrieNode();
    for (int i = 0; i + 9 < s.size(); ++i) {
      string_view str(s.c_str() + i, 10);
      if (ans.find(str) != ans.end()) continue;
      // Add Tire node
      TrieNode* p = root;
      for (char c : str) {
        int i = charToInt(c);
        if (!p->next[i]) {
          p->next[i] = new TrieNode();
        }
        p = p->next[i];
      }
      if (p->exist) {
        ans.emplace(string(str.data(), str.size()));
      } else {
        p->exist = true;
      }
    }

    return vector<string>(ans.begin(), ans.end());
  }

private:
  struct TrieNode {
    bool exist;
    array<TrieNode*, 4> next;
    TrieNode()
      : exist(false), 
        next(array<TrieNode*, 4>{nullptr, nullptr, nullptr, nullptr}){}
  };

  inline int charToInt(char c) {
    switch(c) {
    case 'A':
      return 0;
    case 'C':
      return 1;
    case 'G':
      return 2;
    default: // case 'T'
      return 3;
    }
  }
};
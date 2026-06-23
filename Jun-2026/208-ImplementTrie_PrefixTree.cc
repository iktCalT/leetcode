#include <algorithm>
#include <array>
#include <memory>
#include <string>

using namespace std;

struct TrieNode {
  bool is_end;
  array<TrieNode*, 26> children;

  TrieNode(bool is_end) : is_end(is_end) {
    fill(children.begin(), children.end(), nullptr);
  }
};

class Trie {
private:
  TrieNode* root;
public:
  Trie() {
    // word and prefix consist only of lowercase English letters
    root = new TrieNode(false);
  }
  
  void insert(string word) {
    auto [i, node] = goFurthest(root, word);
    if (i != word.size()) {
      for (; i < word.size(); ++i) {
        // node->children[word[i] - 'a'] must be nullptr, don't need 
        // conditional statements
        node->children[word[i] - 'a'] = new TrieNode(false);
        node = node->children[word[i] - 'a'];
      }
    }
    node->is_end = true;
  }
  
  bool search(string word) {
    auto [i, node] = goFurthest(root, word);
    if (i == word.size() && node->is_end == true) return true;
    return false;
  }
  
  bool startsWith(string prefix) {
    auto [i, node] = goFurthest(root, prefix);
    if (i == prefix.size()) return true;
    return false;
  }

private: 
  pair<int, TrieNode*> goFurthest(TrieNode* node, const string& str) {
    // return the furthest pointer of Trie 
    // and the corresponding index of char
    int i;
    for (i = 0; i < str.size(); ++i) {
      if (node->children[str[i] - 'a'] == nullptr) break;
      node = node->children[str[i] - 'a'];
    }

    return {i, node};
  }
};


struct TrieNodeSmart {
  bool is_end;
  array<shared_ptr<TrieNodeSmart>, 26> children;

  TrieNodeSmart(bool is_end) : is_end(is_end) {}
};

class TrieSmart {
private:
  shared_ptr<TrieNodeSmart> root;
public:
  TrieSmart() {
    // word and prefix consist only of lowercase English letters
    root = make_shared<TrieNodeSmart>(false);
  }
  
  void insert(string word) {
    auto [i, node] = goFurthest(root, word);
    if (i != word.size()) {
      for (; i < word.size(); ++i) {
        // node->children[word[i] - 'a'] must be nullptr, don't need 
        // conditional statements
        node->children[word[i] - 'a'] = make_shared<TrieNodeSmart>(false);
        node = node->children[word[i] - 'a'];
      }
    }
    node->is_end = true;
  }
  
  bool search(string word) {
    auto [i, node] = goFurthest(root, word);
    if (i == word.size() && node->is_end == true) return true;
    return false;
  }
  
  bool startsWith(string prefix) {
    auto [i, node] = goFurthest(root, prefix);
    if (i == prefix.size()) return true;
    return false;
  }

private: 
  pair<int, shared_ptr<TrieNodeSmart>> goFurthest(shared_ptr<TrieNodeSmart> node, const string& str) {
    // return the furthest pointer of Trie 
    // and the corresponding index of char
    int i;
    for (i = 0; i < str.size(); ++i) {
      if (node->children[str[i] - 'a'] == nullptr) break;
      node = node->children[str[i] - 'a'];
    }

    return {i, node};
  }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

int main() {
  Trie* obj = new Trie();
  string word = "apple";
  obj->insert(word);
  bool param_2 = obj->search(word);
  bool param_3 = obj->startsWith(word);
}
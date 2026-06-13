#include <array>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  int countOfSubstrings(string word, int k) {
    int ans = 0;
    // cnt[0] to cnt[4], count of aeiou; cnt[5]: count of consonants
    array<int, 6> cnt{0, 0, 0, 0, 0};
    bool is_valid = false;
    int l = 0, r = 0;
    cnt[char2int(word[0])] = 1;
    while (l < word.size() - 4) {
      // init
      while (cnt[5] < k && r < word.size()) {
        // move r to right
        ++r;
        ++cnt[char2int(word[r])];
        if (!is_valid)
          is_valid = validate(cnt, k);
      }

      if (cnt[5] < k) {
        // r reaches the end
        break;
      }

      // search, only ans can be changed
      while (cnt[5] == k && l < word.size() - 4) {
        search(l, r, word, cnt, ans, k, is_valid);
        if (l < r) {
          --cnt[char2int(word[l])];
          if (is_valid && cnt[char2int(word[l])] == 0)
            is_valid = false;
          ++l;
        } else {
          ++l;
          r = l;
          cnt = {0,0,0,0,0};
          cnt[char2int(word[r])] = 1;
          is_valid = false;
          break;
        }
      }

      if (cnt[5] > k) {
        while (char2int(word[l]) == 5 && l < word.size()) {
          ++l;
        }
        r = l;
        cnt = {0,0,0,0,0};
        cnt[char2int(word[r])] = 1;
        is_valid = false;
      }
    }
    return ans;
  }

private:
  int char2int(char c) {
    switch (c) {
    case 'a':
      return 0;
    case 'e':
      return 1;
    case 'i':
      return 2;
    case 'o':
      return 3;
    case 'u':
      return 4;
    default:
      return 5;
    }
  }

  bool validate(const array<int, 6> &cnt, int k) {
    if (cnt[5] != k)
      return false;
    for (int _ = 0; _ < 5; ++_) {
      if (!cnt[_])
        return false;
    }
    return true;
  }

  void search(int l, int r, const string &word, array<int, 6> cnt, int &ans,
              int k, bool is_valid) {
    // return the next right pointer
    while (cnt[5] == k && r < word.size()) {
      // move r to right
      ans += is_valid;
      ++r;
      ++cnt[char2int(word[r])];
      if (!is_valid)
        is_valid = validate(cnt, k);
    }
  }
};

int main() {
  Solution demo;
  std::cout << demo.countOfSubstrings("cafuogeuoic", 0) << "\n";
}
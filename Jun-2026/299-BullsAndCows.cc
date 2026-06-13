#include <array>
#include <string>

using namespace std;

class Solution {
public:
  string getHint(string secret, string guess) {
    // 1st round: find out bulls, and erase
    int bulls = 0;
    for (int i = 0; i < secret.size(); ++i) {
      if (secret[i] == guess[i]) {
        fastErase(secret, i);
        fastErase(guess, i);
        ++bulls;
        // now, i is pointing to next position, we need to subtract 1
        --i;
      }
    }

    // 2nd round: find out cows - use array
    array<char, 10> cnt;
    for (char digit : secret) {
      ++cnt[digit - '0'];
    }

    for (char digit : guess) {
      --cnt[digit - '0'];
    }
    // cows = secret.size() - sum(positive)
    // sum(positive) = sum(negative) = unmatched digits
    int cows = secret.size();
    for (int i : cnt) {
      cows -= i > 0 ? i : 0;
    }

    string ans = to_string(bulls) + "A" + to_string(cows) + "B";
    return ans;
  }

private:
  void fastErase(string& str, int pos) {
    str[pos] = str.back();
    str.pop_back();
  }
};


class Solution0 {
public:
  string getHint(string secret, string guess) {
    // 1st round: find out bulls, and erase
    int bulls = 0;
    for (int i = 0; i < secret.size(); ++i) {
      if (secret[i] == guess[i]) {
        fastErase(secret, i);
        fastErase(guess, i);
        ++bulls;
        // now, i is pointing to next position, we need to subtract 1
        --i;
      }
    }

    // 2nd round: find out cows
    sort(secret.begin(), secret.end());
    sort(guess.begin(), guess.end());
    int cows = 0;
    int ps = 0, pg = 0; // pointer of secret and pointer of guess
    while (ps < secret.size() && pg < secret.size()) {
      if (secret[ps] == guess[pg]) {
        ++cows;
        ++ps;
        ++pg;
      } else if (secret[ps] < guess[pg]) {
        ++ps;
      } else {
        ++pg;
      }
    }

    string ans = to_string(bulls) + "A" + to_string(cows) + "B";
    return ans;
  }

private:
  void fastErase(string& str, int pos) {
    str[pos] = str.back();
    str.pop_back();
  }
};
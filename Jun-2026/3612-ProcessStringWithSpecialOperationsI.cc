#include <string>

using namespace std;

class Solution { // 0ms use ans += ans to replace ans.insert()
public:
  string processStr(string s) {
    string ans;
    ans.reserve(1 << (s.size() - 1));
    
    bool reversed = false;
    for (char& c : s) {
      switch (c) {
      case '*':
      // pop back
        if (ans.size() != 0) {
          ans.erase(reversed ? ans.begin() : ans.end() - 1);
        }
        break;
      case '#':
      // duplicate
        ans += ans;
        break;
      case '%':
      // reverse
        reversed = !reversed;
        break;
      default:
        ans.insert(reversed ? ans.begin() : ans.end(), c);
      }
    }

    if (reversed) reverse(ans.begin(), ans.end());
    return ans;
  }
};

class Solution2 { // 1ms reserve enough space
public:
  string processStr(string s) {
    string ans;
    ans.reserve(1 << (s.size() - 1));
    
    bool reversed = false;
    for (char& c : s) {
      switch (c) {
      case '*':
      // pop back
        if (ans.size() != 0) {
          ans.erase(reversed ? ans.begin() : ans.end() - 1);
        }
        break;
      case '#':
      // duplicate
        ans.insert(ans.end(), ans.begin(), ans.end());
        break;
      case '%':
      // reverse
        reversed = !reversed;
        break;
      default:
        ans.insert(reversed ? ans.begin() : ans.end(), c);
      }
    }

    if (reversed) reverse(ans.begin(), ans.end());
    return ans;
  }
};

class Solution1 { // 4ms
public:
  string processStr(string s) {
    string ans;
    bool reversed = false;
    for (char& c : s) {
      switch (c) {
      case '*':
      // pop back
        if (ans.size() != 0) {
          ans.erase(reversed ? ans.begin() : ans.end() - 1);
        }
        break;
      case '#':
      // duplicate
        ans.insert(ans.end(), ans.begin(), ans.end());
        break;
      case '%':
      // reverse
        reversed = !reversed;
        break;
      default:
        ans.insert(reversed ? ans.begin() : ans.end(), c);
      }
    }

    if (reversed) reverse(ans.begin(), ans.end());
    return ans;
  }
};

class Solution0 { // 4ms
public:
  string processStr(string s) {
    string ans;
    for (char& c : s) {
      switch (c) {
      case '*':
        if (ans.size() != 0) ans.pop_back();
        break;
      case '#':
        ans.insert(ans.end(), ans.begin(), ans.end());
        break;
      case '%':
        reverse(ans.begin(), ans.end());
        break;
      default:
        ans.push_back(c);
      }
    }
    return ans;
  }
};
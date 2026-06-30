#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  string kthDistinct(vector<string>& arr, int k) {
    unordered_map<string, bool> dst;
    for (const string& s : arr) {
      if (dst.contains(s)) dst[s] = false;
      else dst.insert({s, true});
    }

    if (k > dst.size()) return "";

    for (const string& s : arr) {
      if (dst[s] == false)  continue;

      --k;
      if (k == 0) {
        return s;
      }
    }
    return "";
  }
};

class Solution1 { // 54ms
public:
  string kthDistinct(vector<string> &arr, int k) { 
    // 1 <= arr[i].length <= 5, we can store the entire string
    vector<string> dst; // distinct strings
    for (auto cit = arr.cbegin(); cit != arr.cend(); ++cit) {
      if (find(arr.cbegin(), cit, *cit) != cit) {
        auto it = find(dst.begin(), dst.end(), *cit);
        if (it != dst.end())
          dst.erase(it);
      } else {
        dst.push_back(*cit);
      }
    }

    if (dst.size() < k)
      return "";
    return dst[k - 1];
  }
};

class Solution0 { // 52ms
public:
  string kthDistinct(vector<string> &arr, int k) {
    // 1 <= arr[i].length <= 5, we can store the entire string
    vector<string> dst; // distinct strings
    unordered_set<string> evicted;
    for (const string &s : arr) {
      if (evicted.contains(s))
        continue;
      if (auto it = find(dst.begin(), dst.end(), s); it != dst.end()) {
        evicted.insert(s);
        dst.erase(it);
      } else {
        dst.push_back(s);
      }
    }

    if (dst.size() < k)
      return "";
    return dst[k - 1];
  }
};

int main() {
  Solution demo;
  vector<string> arr{"aaa", "aa", "a"};
  std::cout << demo.kthDistinct(arr, 1) << "\n";
}
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Solution {
private:
  static bool compare (const string& lhs, const string& rhs) {
    string lr = lhs + rhs;
    string rl = rhs + lhs;
    return lr > rl;
  }
public:
  string largestNumber(vector<int>& nums) {
    vector<string> strs;
    strs.reserve(nums.size());
    for (const int i : nums) {
      strs.push_back(to_string(i));
    }

    sort(strs.begin(), strs.end(), compare);

    string ans;
    for (string s : strs) {
      if (ans.empty() && s == "0") continue;
      ans = ans + s;
    }
    if (ans.empty()) return "0";
    return ans;
  }
};
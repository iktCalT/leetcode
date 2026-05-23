#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, int> groups_ref;
    vector<int> groups(strs.size());

    for (int i = 0; i < strs.size(); i++) {
      string str = strs[i]; // str is a copy
      sort(str.begin(), str.end());

      if (groups_ref.find(str) == groups_ref.end()) {
        groups_ref.insert({str, groups_ref.size()});
      }
      groups[i] = groups_ref[str];
    }

    vector<vector<string>> ans(groups_ref.size());
    for (int i = 0; i < groups.size(); i++) {
      ans[groups[i]].push_back(strs[i]);
    }
    return ans;
  }
};

class SolutionSlow {
public:
  // Although it's more structural to create a class Group
  // We need to copy vec in each Group to answer, making the function slow
  // class Group {
  //     string letters;
  //     vector<string> vec;

  //     Group(string str)
  //         : vec{str}, letter(sort(str.begin(), str.end())) {}

  //     add(string str) {
  //         vec.push_back(str);
  //     }
  // };

  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    // Cannot use *tire*, because 1 <= strs.length <= 10^4
    // space occupation will explode
    vector<vector<string>> ans;
    vector<string> reps; // representations

    for (string &str : strs) {
      string rep = str;
      sort(rep.begin(), rep.end());

      auto it = find(reps.begin(), reps.end(), rep);
      if (it == reps.end()) {
        // does not belong to any existing group
        ans.emplace_back(vector<string>{str});
        reps.push_back(rep);
      } else {
        ans[distance(reps.begin(), it)].push_back(str);
      }
    }

    return ans;
  }
};
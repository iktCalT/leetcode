#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  int countStaircase(vector<int>& nums) {
    int n = nums.size();
    int count = n;
    for (int start = 0; start < n; ++start) {
      unordered_map<int, pair<int, int>> hist;
      hist.try_emplace(nums[start], 1, 1);
      int satisfy = 1;
      for (int len = 1, add = 2; start + len + add - 1 < n; len += add, ++add) {
        for (int i = start + len; i < start + len + add; ++i) {
          auto [it, success] = hist.try_emplace(nums[i], hist.size() + 1, 1);
          if (!success) {
            int tmp = ++it->second.second;
            if (it->second.first == tmp)
              satisfy += 1;
            else if (it->second.first == tmp - 1) 
              satisfy -= 1;
          }
        }
        
        if (satisfy == add)
          ++count;
      }
    }
    return count;
  }
};
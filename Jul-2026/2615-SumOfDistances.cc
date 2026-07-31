#include <unordered_map>
#include <vector>
using namespace std;

struct Sum {
  long long sum;
  int cnt;
  int cur;
};

class Solution {
public:
  vector<long long> distance(vector<int>& nums) {
    unordered_map<int, Sum> sum;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      auto it = sum.find(nums[i]);
      if (it == sum.end()) {
        sum.emplace(nums[i], Sum{i, 1, 0});
      } else {
        it->second.sum += i;
        ++it->second.cnt;
      }
    }

    vector<long long> ans(n);
    for (long long i = 0; i < n; ++i) {
      Sum& tmp = sum[nums[i]];
      ans[i] = tmp.sum - i * (tmp.cnt - 2 * tmp.cur);
      tmp.sum -= i * 2; // tmp is reference
      ++tmp.cur;
    }
    return ans;
  }
};
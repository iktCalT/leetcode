#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int maximumLength(vector<int>& nums) {
    // Notice that 1 <= nums[i] <= 10^9
    // nums[i] * nums[i] could exceed int's boundary

    // Pair {base, ppower} means base * (2 ^ ppower)

    // e.g. pair {3, {2, 0, 3}} means 
    // having 2 (3 ^ (2 ^ 0)), 0 (3 ^ (2 ^ 1)), and 3 (3 ^ (2 ^ 2))
    // meaning nums have: 3, 3, 81, 81, 81
    unordered_map<int, vector<int>> groups; // base, ppowers
    groups.insert({1, {0}});
    for (const int num : nums) {
      auto [base, ppower] = parse(num);
      auto it = groups.find(base);
      if (it == groups.end()) { // found
        it = groups.insert({base, {}}).first;
      }
      addPPower(ppower, it->second);
    }

    // if we have 9 or 10 ones, answer should be at least 9
    int ans = ((groups[1][0] - 1) / 2) * 2 + 1;
    groups.erase(1);
    for (const auto& group : groups) {
      int tmp = getMaxIndex(group.second);
      ans = max(ans, tmp * 2 - 1);
    }
    return ans;
  }

private:
  int getMaxIndex(const vector<int>& ppowers) {
    // e.g. {1,0,1,3,4,6,1,5,5,5} return 4 -> 3,4,6,1
    //      {1,0,1,3,4,6,0,5,5,5} return 3 -> 3,4,6
    int ans = 0;
    int cnt = 0;
    for (const int pp : ppowers) {
      if (pp > 1) {
        ++cnt;
      }
      else if (pp == 1) {
        ++cnt;
        ans = max(ans, cnt);
        cnt = 0;
      } else {
        ans = max(ans, cnt);
        cnt = 0;
      }
    }
    ans = max(ans, cnt);
    return ans;
  }

  void addPPower (int ppower, vector<int>& ppowers) {
    // add 1 to ppowers[ppower]
    if (ppowers.size() < ppower + 1) {
      ppowers.resize(ppower + 1, 0); // resize, fill with zeros
    }
    ++ppowers[ppower];
  }

  pair<int, int> parse(int num) {
    // If num == base ^ (2 ^ ppower), 
    // where base and ppower are positive integers, 
    // return {base, ppower}
    if (num == 1) return {1, 0};

    int ppower = 0;
    while (true) {
      int sqr = sqrt(num);
      if (sqr * sqr != num) break;
      num = sqr;
      ++ppower;
    }
    return {num, ppower};
  }
};
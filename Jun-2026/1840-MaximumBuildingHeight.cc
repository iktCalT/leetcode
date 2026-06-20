#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Restriction {
  int pos;
  int height;
  int max_height;
};

class Solution { // Runtime 43 ms Beats 93.06%
public:
  int maxBuilding(int n, vector<vector<int>>& restrictions) {
    // For building i, its height determined by
    // 0. height[1] = 0
    // 1. height[i-1] - 1 <= height[i] <= height[i-1] + i
    // 2. for j: 0 <= height[i] <= restriction[j] + abs(i - j)

    // The highest building between any two restrictions r1, r2 (r1[0] < r2[0]) is
    // ((r2[0] - r1[0] - 1) - abs(r1[1] - r2[1]) + 1) / 2 + max(r1[1], r2[1])
    // = (r2[0] - r1[0] + r1[1] + r2[1]) / 2
    // e.g. [7, 4], [11, 3] -> height[7 to 11]: 4, 5, 5, 4, 3 -> 5

    // Some restrictions are useless, e.g. in [7, 4], [9, 100], [11, 3]
    // [9, 100] is useless, we only need to record the previous useful restriction
    // Useful restrictions: r[1] < r[0] + previous_r[1] - previous_r[0]
    // We just need to compare their r[1] - r[0]
    
    // Let's go through all restrictions (sorted), if encountered a 
    // "useful" restriction, get the local highest height, and renew the 
    // global highest height.

    // Be careful: if [7, 4], [9, 5], [10, 1]
    // although: 4, 5, 5 is okay for 7 to 9, but it cannot fullfill restriction
    // [10, 1]. So, we need to record ALL "useful" restrictions, rather than 1

    // A second possible answer is determined by the last "useful" restriction
    // e.g. [7, 4], [9, 5], [11, 12], [13, 5], [14, 100], n = 1000
    // useful restrictions: [7, 4] -> [9, 5] -> [13, 5]
    // height in between: [7, 4] -> 5 -> [9, 5] -> 7 -> [13, 5] => choose 7
    // height in the end: 1000 - (13 - 5) = 992
    // return 992

    // O(mlog(m)), m = restrictions.size()
    sort(restrictions.begin(), restrictions.end(), 
      [](vector<int>& lhs, vector<int>& rhs){return lhs[0] < rhs[0];});

    stack<Restriction> useful_r; // previous useful restriction
    useful_r.push({1, 0}); 
    int diff = -1; // r1 - r0

    for (const auto& r : restrictions) {
      if (r[1] - r[0] < diff) {
        // find highest in between
        maxHeight(r, useful_r);
        diff = r[1] - r[0];
      }
    }

    int end_height = n - (useful_r.top().pos - useful_r.top().height);

    int max_height = 0;
    while (!useful_r.empty()) {
      max_height = max(max_height, useful_r.top().max_height);
      useful_r.pop();
    }
    return max(max_height, end_height);
  }

private:
  void maxHeight(const vector<int>& r, stack<Restriction>& useful_r) {
    while (true) { // don't need while(!prev_r.empty())
                   // it cannot be empty, because it has {1, 0}
      auto pr = useful_r.top();
      if (pr.pos + pr.height > r[0] + r[1]) {
        useful_r.pop(); // this is not useful
        continue;
      }

      int highest = (r[0] - pr.pos + r[1] + pr.height) / 2;
      useful_r.emplace(r[0], r[1], highest);
      break;
    }
  }
};

int main() {
  Solution demo;
  vector<vector<int>> rest 
    {{68,29},{89,27},{66,26},{34,9},{53,23},{93,24},{70,12},{25,24},{5,4},{94,41},{51,42},{6,39},{55,21},{69,9},{39,50},{99,42},{77,24},{81,46},{90,43},{27,14},{31,5},{67,37},{82,10},{26,47},{84,34},{37,30},{83,39},{21,39},{49,39},{13,48},{12,34},{57,0},{7,43},{17,6},{23,0},{86,30},{47,30},{61,19},{30,49},{95,42},{3,31},{33,36},{11,45},{75,39},{85,46},{29,33},{2,9},{22,17},{65,42},{96,0},{35,46},{88,47},{74,0},{73,47},{41,45},{15,21},{97,0},{64,0},{40,21},{76,2},{54,3},{24,33},{45,24},{16,23},{91,14},{43,35},{79,6},{46,30},{71,3},{9,39},{50,21},{48,45},{63,42},{58,3},{10,26},{4,6},{52,19},{32,39},{87,50},{8,48},{19,25},{92,1},{28,21},{59,31},{72,24},{78,9},{100,8},{60,20},{42,16},{38,8},{62,31},{36,22},{44,27},{14,45},{18,3},{98,0},{20,1},{56,24},{80,3}};
  std::cout << demo.maxBuilding(5, rest) << "\n";
}
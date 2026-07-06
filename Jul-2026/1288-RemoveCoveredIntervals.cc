#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  int removeCoveredIntervals(vector<vector<int>>& intervals) {
    // Notice that: 1 <= intervals.length <= 1000, 
    // 0 <= li < ri <= 10^5. It would be better to
    // iterate through intervals than li, ri.

    // If first k intervals are handled and sorted (by
    // their li, ascending order). When we are going to 
    // handle interval[k], we need to 1. find its position
    // by binary search. 2. will it be covered by its left 
    // adjacent interval? 3. how many right intervals can it
    // cover?

    // Or, we can make it simpler (but slower), sort all 
    // elements first and then check if it can cover any
    // element on its right

    sort(intervals.begin(), intervals.end(), 
  [](const vector<int>& lhs, const vector<int>& rhs){return lhs[0] < rhs[0];});
    for (int i = 0; i < intervals.size(); ++i) {
      int li = intervals[i][0]; // copy, faster
      int ri = intervals[i][1];
      for (int j = i + 1; j < intervals.size(); ++j) {
        // we already know that lj >= li, but 
        // if lj == li, we don't know if rj >= ri
        int rj = intervals[j][1];

        // lj == li case
        if (intervals[j][0] == li) {
          intervals[i][1] = max(ri, rj);
          ri = intervals[i][1];
          intervals.erase(intervals.begin() + j);
          --j;
          continue;
        }

        // If lj > li && rj > ri -> not covered
        if (rj > ri) continue;

        // If lj > li && rj <= ri -> covered
        intervals.erase(intervals.begin() + j);
        --j;
      }
    }
    return intervals.size();
  }
};

int main() {
  Solution demo;
  vector<vector<int>> nums{{1,4},{3,6},{2,8},{4,5},{1,2}};
  demo.removeCoveredIntervals(nums);
}
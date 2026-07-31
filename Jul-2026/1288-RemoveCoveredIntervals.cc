#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class Solution { // 0ms
public:
  int removeCoveredIntervals(vector<vector<int>>& intervals) {
    // Optimize by using ordered map
    map<int, int> solution;
    solution.emplace(intervals[0][0], intervals[0][1]);

    for (auto it = intervals.begin() + 1; 
                it != intervals.end(); ++it) {

      auto& intv = *it; // interval
      auto pos = solution.lower_bound(intv[0]);
      // covered by previous interval? If not, insert interval
      if (pos->first == intv[0] && pos->second < intv[1]) {
        // insert by replacing *pos
        pos->second = intv[1];
      } else if (pos == solution.begin()
              || prev(pos)->second < intv[1]) {
        // insert
        solution.insert(pos, {intv[0], intv[1]});
      } else {
        // just skip this interval
        continue;
      }
    
      // cover latter intervals
      --pos;
      while (next(pos) != solution.end()) {
        if (next(pos)->second > intv[1]) break;
        solution.erase(next(pos));
      }
    }

    return solution.size();
  }
};

class Solution2 { // 1ms
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

    // map should be faster, since it don't rearrange in erasing
    vector<pair<int, int>> solution;
    solution.emplace_back(intervals[0][0], intervals[0][1]);

    for (vector<int> interval : intervals) {
      int i = binary_search(interval[0], solution);
      // insert interval (after this, solution[i] is interval)
      if (i != solution.size() && solution[i].first == interval[0] && solution[i].second < interval[1]) {
        solution[i].second = interval[1];
      } else if (i == 0 
          || solution[i - 1].second < interval[1]) {
        // not covered, insert
        solution.emplace(solution.begin() + i, interval[0], interval[1]);
      } else {
        // just skip this interval
        continue;
      }
    
      // cover latter intervals
      while (i + 1 < solution.size()) {
        // If solution[i + 1] cannot cover solution[i + k] (k > 1). 
        // Then solution[i] cannot cover solution[i + k], too
        if (solution[i + 1].second > interval[1]) break;
        solution.erase(solution.begin() + i + 1);
      }
    }

    return solution.size();
  }

private:
  int binary_search(int val, 
      const vector<pair<int, int>>& vec) {
    // Return the index of first element, whose
    // first value is greater than val. If val 
    // is greater than all elements' first, return n
    // Notice that all element's first are unique
    int lo = -1;
    int hi = vec.size();
    if (hi == 1) return val > vec[0].first;

    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;
      if (vec[mid].first == val) {
        return mid;
      } else if (vec[mid].first > val) {
        hi = mid;
      } else if (vec[mid].first < val) {
        lo = mid;
      }
    }
    return hi;
  }
};

class Solution1 { // 47ms
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
  vector<vector<int>> nums{{1,2},{1,4},{3,4}};
  demo.removeCoveredIntervals(nums);
}
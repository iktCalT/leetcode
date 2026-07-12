#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// 39ms
class Solution {
public:
  vector<int> arrayRankTransform(vector<int>& arr) {
    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());

    unordered_map<int, int> rank;
    int no = 1;
    for (const auto& val : sorted) {
      if (rank.find(val) != rank.end()) continue;

      rank.emplace(val, no);
      ++no;
    }

    int n = arr.size();
    for (int i = 0; i < n; ++i) {
      arr[i] = rank[arr[i]];
    }
    return arr;
  }
};

// 76ms
class Solution3 {
public:
  vector<int> arrayRankTransform(vector<int>& arr) {
    map<int, int> rank;
    for (const auto& val : arr) {
      rank.try_emplace(val, 0);
    }

    int no = 1;
    for (auto& r : rank) {
      r.second = no;
      ++no;
    }

    int n = arr.size();
    for (int i = 0; i < n; ++i) {
      arr[i] = rank[arr[i]];
    }
    return arr;
  }
};

// TLE
class Solution2 {
public:
  vector<int> arrayRankTransform(vector<int>& arr) {
    vector<int> rank = arr;
    // sort
    sort(rank.begin(), rank.end());
    // remove duplicated elements
    int n = arr.size();
    for (auto it = arr.begin() + 1; it != arr.end(); ++it) {
      if (*it == *(it - 1)) {
        it = arr.erase(it);
      }
    }

    unordered_map<int, int> lookup_table;
    for (int i = 0; i < n; ++i) {
      auto it = lookup_table.find(arr[i]);
      if (it != lookup_table.end()) {
        arr[i] = it->second;
      } else {
        int r = binarySearch(arr[i], rank) + 1;
        lookup_table.insert({arr[i], r});
        arr[i] = r;
      }
    }
    return arr;
  }

private:
  int binarySearch(int val, vector<int> vec) {
    int lo = -1;
    int hi = vec.size();
    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;
      if (vec[mid] == val) return mid;

      if (vec[mid] > val) {
        hi = mid;
      } else {
        lo = mid;
      }
    }
    return hi;
  }
};

// TLE
class Solution1 {
public:
  vector<int> arrayRankTransform(vector<int>& arr) {
    set<int> rank(arr.begin(), arr.end());

    int n = arr.size();
    for (int i = 0; i < n; ++i) {
      arr[i] 
        = distance(rank.begin(), rank.lower_bound(arr[i])) 
        + 1;
    }
    return arr;
  }
};

/* LowerBound in vector:
  int lowerBound(int val, vector<int> vec) {
    int lo = -1;
    int hi = vec.size();
    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;
      if (vec[mid] >= val) {
        hi = mid;
      } else {
        lo = mid;
      }
    }
    return hi;
  } 
 */

// 75ms
class Solution0 {
public:
  vector<int> arrayRankTransform(vector<int>& arr) {
    map<int, vector<int>> rank;
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
      auto it = rank.find(arr[i]);
      if (it == rank.end()) {
        rank.emplace(arr[i], vector<int>{i});
      } else {
        it->second.push_back(i);
      }
    }

    int r = 1;
    for (const auto& item : rank) {
      const vector<int>& positions = item.second;
      for (int pos : positions) {
        arr[pos] = r;
      }
      ++r;
    }
    return arr;
  }
};
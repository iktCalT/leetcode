#include <algorithm>
#include <climits>
#include <functional>
#include <iterator>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

class Solution { // Runtime 1251 ms Beats 5.94%; Memory 335.81 MB Beats 77.23%
public:
  vector<bool> getResults(vector<vector<int>>& queries) {
    vector<bool> ans;
    // key: gap, value: starting positions
    // gaps's key is sorted in descending order, 
    // while its values are vectors sorted in ascending order
    map<int, vector<int>, greater<int>> gaps{{INT_MAX, {0}}};
    // position of obstacles (sorted)
    vector<int> obs{0, INT_MAX};

    for (const auto& query : queries) {
      if (query[0] == 1) {
        auto [gap, prev, prev_gap] = placeObstacle(query[1], obs);
        removeGap(prev, prev_gap + gap, gaps);
        insertGap(prev, prev_gap, gaps);
        insertGap(query[1], gap, gaps);
      } else {
        ans.push_back(placeBlock(query[1], query[2], gaps));
      }
    }
    return ans;
  }

private:
  int findInSortedVector(int val, const vector<int>& vec) {
    // return hi, where vec[hi - 1] < val <= vec[hi]
    int lo = -1, hi = vec.size(); // notice hi is not obs.size() - 1
    while (hi - lo > 1) {
      int mid = (hi + lo) / 2;
      if (vec[mid] == val) {
        return mid;
      } else if (vec[mid] < val) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    return hi;
  }

  tuple<int, int, int> placeObstacle(int pos, vector<int>& obs) {
    // first return value: gap of inserted position
    // second return value: previous position
    // third return value: new gap of previous position
    // obs is sorted
    int hi = findInSortedVector(pos, obs);
    obs.insert(obs.begin() + hi, pos);
    // after insertion, obs[hi] is pos
    return {obs[hi + 1] - pos, obs[hi - 1], pos - obs[hi - 1]};
  }

  void insertGap(int pos, int gap, map<int, vector<int>, greater<int>>& gaps) {
    if (gaps.find(gap) != gaps.end()) {
      int hi = findInSortedVector(pos, gaps[gap]);
      gaps[gap].insert(gaps[gap].begin() + hi, pos); // sorted
    } else {
      gaps.insert({gap, {pos}});
    }
  }

  void removeGap(int pos, int old_gap, map<int, vector<int>, greater<int>>& gaps) {
    // old_gap must be in gaps. gaps.find(gap) != gaps.end() is unnecessary
    if (gaps[old_gap].size() == 1) {
      gaps.erase(old_gap);
      return;
    }
    int hi = findInSortedVector(pos, gaps[old_gap]);
    gaps[old_gap].erase(gaps[old_gap].begin() + hi);
  }

  bool placeBlock(int end, int size, const map<int, vector<int>, greater<int>>& gaps) {
    for (auto cit = gaps.cbegin(); cit != gaps.cend(); ++cit) {
      if (cit->first < size) break;
      if (cit->second[0] + size <= end) return true;
    }

    return false;
  }
};

class SolutionSlow {
public:
  vector<bool> getResults(vector<vector<int>>& queries) {
    // Positions of obstacles
    vector<int> obstacles{0, INT_MAX};
    vector<bool> ans;
    bool sorted;
    for (const auto& query : queries) {
      if (query[0] == 1) {
        placeObstacle(query[1], obstacles);
        sorted = false;
      } else {
        // lazy sort - sort only before placing blocks
        if (!sorted) {
          sort(obstacles.begin(), obstacles.end());
          sorted = true;
        }
        ans.push_back(placeBlock(query[1], query[2], obstacles));
      }
    }
    return ans;
  }

private:
  inline void placeObstacle(int pos, vector<int>& obstacles) {
    obstacles.push_back(pos);
  }

  bool placeBlock(int end, int size, vector<int>& obstacles) {
    // We don't need (i < obstacles.size()), 
    // (obstacles[i] < end) is enough, 
    // because obstacles.back() == INT_MAX
    for (int i = 0; obstacles[i] < end; ++i) {
      int gap = min(end, obstacles[i + 1]) - obstacles[i];
      if (gap >= size) return true;
    }

    return false;
  }
};

class SolutionSlow2 {
public:
  vector<bool> getResults(vector<vector<int>>& queries) {
    // Positions of obstacles, and distance to next obstacle
    map<int, int> obstacles{{0, INT_MAX}};
    vector<bool> ans;
    for (const auto& query : queries) {
      if (query[0] == 1) {
        placeObstacle(query[1], obstacles);
      } else {
        ans.push_back(placeBlock(query[1], query[2], obstacles));
      }
    }
    return ans;
  }

private:
  void placeObstacle(int pos, map<int, int>& obstacles) {
    auto it = obstacles.upper_bound(pos);
    obstacles.insert(it, {pos, 0});
    --it;
    it->second = (prev(it)->second + prev(it)->first - pos);
    prev(it)->second = pos - prev(it)->first;
  }

  bool placeBlock(int end, int size, const map<int, int>& obstacles) {
    auto cit = obstacles.upper_bound(end);
    // cit != obstacles.cbegin()
    --cit;
    if (min(end - cit->first, cit->second) >= size) {
      return true;
    }

    while(cit != obstacles.cbegin()) {
      --cit;
      if (cit->second >= size) return true;
    }

    return false;
  }
};

int main() {
  Solution demo;
  vector<vector<int>> q {{1,7},{2,7,6},{1,2},{2,7,5},{2,7,6}};
  demo.getResults(q);
}
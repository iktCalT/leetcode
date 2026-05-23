#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

class Solution {
public:
  int maximumJumps(std::vector<int> &nums, int target) {
    // dp, from end to beginning
    int size = nums.size();
    std::vector<int> stateList(size, -1);
    stateList[size - 1] = 0;

    for (int current = size - 2; current >= 0; current--) {
      for (int next = current + 1; next < size; next++) {
        if (abs(nums[next] - nums[current]) <= target && stateList[next] != -1) {
          stateList[current] = std::max(stateList[current], stateList[next] + 1);
        }
      }
    }

    return stateList[0];
  }
};

class SolutionSlow {
public:
  int maximumJumps(std::vector<int> &nums, int target) {
    // Create an action table: for index i, the array of possible j
    // DP: from end to start, for each index, list its max jumps to target
    const auto at = createActionTable(nums, target);
    return jumpToLast(at);
  }

private:
  std::vector<std::vector<int>> createActionTable(const std::vector<int> &nums,
                                                  const int step) {
    std::vector<std::vector<int>> at; // action table
    for (int i = 0; i < nums.size(); i++) {
      at.emplace_back(std::vector<int>{});
      for (int j = i + 1; j < nums.size(); j++) {
        if (std::abs(nums[j] - nums[i]) <= step)
          at.back().push_back(j);
      }
    }
    return at;
  }

  struct State {
    bool possible = false;
    int maxJumps = -1;

    void setMaxJumps(int maxJumps) {
      this->maxJumps = maxJumps;
      if (maxJumps >= 0) {
        possible = true;
      }
    }
  };

  int jumpToLast(const std::vector<std::vector<int>> &at) {
    // initialize a list of states
    int size = at.size();
    std::vector<State> stateList;
    stateList.reserve(size);
    for (int i = 0; i < stateList.capacity(); i++) {
      stateList.emplace_back(State{});
    }
    stateList.back().setMaxJumps(0);

    // loop
    for (int current = size - 2; current >= 0; current--) {
      std::vector<int> actions = at[current];
      int maxJumps = -1;
      for (const int& next : actions) {
        if (stateList[next].possible == true) {
          int nJumps = stateList[next].maxJumps + 1;
          maxJumps = std::max(maxJumps, nJumps);
        }
      }
      stateList[current].setMaxJumps(maxJumps);
    }

    return stateList[0].maxJumps;
  }
};

int main() {
  Solution demo;
  std::vector<int> nums{1, 3, 6, 4, 1, 2};
  std::cout << demo.maximumJumps(nums, 2) << std::endl;
}
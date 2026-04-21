#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

// Graph Theory

class Solution {
public:
  int minimumHammingDistance(std::vector<int> &source, std::vector<int> &target,
                             std::vector<std::vector<int>> &allowedSwaps) {
    // 1. Merge allowedSwap pairs into different subgroups
    // 2. For each subgroup, delete source[i] where source[i] == target[i]
    // 3. Count the left-over indexes
    std::vector<std::set<int>> subGroups;
    while (!allowedSwaps.empty()) {
      std::set<int> subGroup{allowedSwaps[0].begin(), allowedSwaps[0].end()};
      allowedSwaps.erase(allowedSwaps.begin());
      MergeSubGroups(allowedSwaps, subGroup);
      subGroups.push_back(subGroup);
    }

    int hammingDist = target.size();
    for (int i = 0; i < target.size(); i++) {
      // find in which subGroup
      std::set<int> subGroup;
      bool found = false;
      for (auto sub : subGroups) {
        if (std::find(sub.begin(), sub.end(), i) != sub.end()) {
          // found!
          found = true;
          subGroup = {sub.begin(), sub.end()};
          break;
        }
      }

      if (!found) { // Not in swap subgroups
        if (source[i] == target[i]) {
          source[i] = 0;
          // Place a tomb sign, because 1 <= source[i], target[i] <= 10^5
          hammingDist--;
        }
      } else {
        for (int j : subGroup) {
          if (source[j] == target[i]) {
            source[j] = 0;
            hammingDist--;
            break;
          }
        }
      }
    }
    return hammingDist;
  }

private:
  void MergeSubGroups(std::vector<std::vector<int>> &allowedSwaps,
                      std::set<int> &subGroup) {
    // Because we erased one element from allowedSwaps before calling this
    // function, allowedSwaps could be empty
    if (allowedSwaps.empty()) {
      return;
    }

    bool stop = false;
    while (!stop) {
      stop = true;
      for (auto it = allowedSwaps.begin(); it < allowedSwaps.end();) {
        if (it->at(0) >= 0 && (std::find(subGroup.begin(), subGroup.end(),
                                         it->at(0)) != subGroup.end() ||
                               std::find(subGroup.begin(), subGroup.end(),
                                         it->at(1)) != subGroup.end())) {
          // If subGroup and swap intersect each other
          stop = false;
          subGroup.insert(subGroup.end(), it->at(0));
          subGroup.insert(subGroup.end(), it->at(1));
          it = allowedSwaps.erase(it);
        } else {
          it++;
        }
      }
    }
  }
};

int main() {
  Solution demo;
  std::vector<int> source{1, 2, 3, 4};
  std::vector<int> target{2, 1, 4, 5};
  std::vector<std::vector<int>> allowedSwaps{{0, 1}, {2, 3}};
  std::cout << demo.minimumHammingDistance(source, target, allowedSwaps)
            << std::endl;

  source = {1, 2, 3, 4};
  target = {2, 1, 4, 5};
  allowedSwaps = {};
  std::cout << demo.minimumHammingDistance(source, target, allowedSwaps)
            << std::endl;

  source = {5, 1, 2, 4, 3};
  target = {1, 5, 4, 2, 3};
  allowedSwaps = {{0, 4}, {4, 2}, {1, 3}, {1, 4}};
  std::cout << demo.minimumHammingDistance(source, target, allowedSwaps)
            << std::endl;
}
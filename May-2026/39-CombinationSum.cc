#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates,
                                               int target) {
    // augment learning ->
    // action: add candidates[0], add candidates[1], add candidates[2], ...
    // state: sum of values
    // punishment: if state > target -> fail
    auto &actions = candidates;
    std::sort(actions.begin(), actions.end());

    std::vector<std::vector<int>> ans;
    int state = 0;
    std::vector<int> path;
    start(ans, target, state, actions, path, 0);

    return ans;
  }

private:
  inline void move(int &state, const std::vector<int> &actions,
                   std::vector<int> &path, int direction) {
    state += actions[direction];
    path.push_back(actions[direction]);
  }

  inline void retreat(int &state, std::vector<int> &path) {
    state -= path.back();
    path.pop_back();
  }

  void start(std::vector<std::vector<int>> &ans, const int target, int &state,
             const std::vector<int> &actions, std::vector<int> &path,
             int direction) {
    for (; direction < actions.size(); direction++) {
      move(state, actions, path, direction);

      if (state == target) {
        ans.push_back(path);
      } else if (state < target) {
        start(ans, target, state, actions, path, direction);
      }

      retreat(state, path);
    }
  }
};

// SLOW!!

struct Wanted {
  int value;
  std::vector<std::vector<int>> paths;

  Wanted(int value, std::vector<std::vector<int>> paths)
      : value(value), paths(paths){};

  bool operator==(const Wanted &other) { return this->value == other.value; }
  bool operator==(const int value) { return this->value == value; }
};

class SolutionSlow {
public:
  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates,
                                               int target) {
    std::sort(candidates.begin(), candidates.end());
    std::vector<Wanted> wantedList;
    for (const int candidate : candidates) {
      // don't worry about negative candidate, because 2 <= candidates[i] <= 40
      std::vector<Wanted> tmp_wantedList;
      for (int multiple = 1; multiple * candidate <= target; multiple++) {
        std::vector<int> tmp_path;
        tmp_path.reserve(multiple);
        for (int _ = 0; _ < multiple; _++) {
          tmp_path.push_back(candidate);
        }
        insertWanted(tmp_wantedList, {multiple * candidate, {tmp_path}});

        for (auto new_wanted : wantedList) { // new_wanted are copies!
          new_wanted.value += multiple * candidate;
          if (new_wanted.value > target) {
            continue;
          }
          for (auto &path : new_wanted.paths) {
            path.insert(path.begin(), tmp_path.begin(),
                        tmp_path.end()); // path is not a copy
          }
          insertWanted(tmp_wantedList, new_wanted);
        }
      }
      combineWantedLists(wantedList, tmp_wantedList);
    }

    auto it = std::find(wantedList.begin(), wantedList.end(), target);
    if (it == wantedList.end()) {
      return {};
    }
    return it->paths;
  }

private:
  void insertWanted(std::vector<Wanted> &wantedList, const Wanted &wanted) {
    // if wanted's value in wantedList, combine their paths; else, insert it
    auto it = std::find(wantedList.begin(), wantedList.end(), wanted);
    if (it != wantedList.end()) {
      it->paths.insert(it->paths.end(), wanted.paths.begin(),
                       wanted.paths.end());
    } else {
      wantedList.push_back(wanted);
    }
  }

  void combineWantedLists(std::vector<Wanted> &primary,
                          const std::vector<Wanted> &secondary) {
    for (const auto &wanted : secondary) {
      insertWanted(primary, wanted);
    }
  }
};

std::ostream &operator<<(std::ostream &stream,
                         const std::vector<int> &vector1D) {
  stream << '[';
  for (auto &element : vector1D) {
    stream << element << ",";
  }
  stream << ']' << std::endl;
  return stream;
}

std::ostream &operator<<(std::ostream &stream,
                         const std::vector<std::vector<int>> &vector2D) {
  stream << '[';
  for (auto &row : vector2D) {
    stream << row << ",";
  }
  stream << "] ";
  return stream;
}

int main() {
  Solution demo;
  std::vector<int> candidates{2, 3, 6, 7, 9};
  std::cout << demo.combinationSum(candidates, 9) << std::endl;
  std::cout << std::endl;
  candidates = {2, 3, 6, 7, 9};
  std::cout << demo.combinationSum(candidates, 11) << std::endl;
  std::cout << std::endl;
  candidates = {7, 3, 2};
  std::cout << demo.combinationSum(candidates, 18) << std::endl;
}
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

struct Wanted {
  int value;
  std::vector<std::vector<int>> paths;

  Wanted(int value, std::vector<std::vector<int>> paths)
      : value(value), paths(paths){};

  bool operator==(const Wanted &other) { return this->value == other.value; }
  bool operator==(const int value) { return this->value == value; }
};

class Solution {
public:
  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates,
                                               int target) {
    std::sort(candidates.begin(), candidates.end());
    std::vector<Wanted> wantedList;
    for (const int candidate : candidates) {
      // don't worry about negative candidate, because 2 <= candidates[i] <= 40
      int end = wantedList.size() - 1;
      for (int multiple = 1; multiple * candidate <= target; multiple++) {
        std::vector<int> tmp_path;
        tmp_path.reserve(multiple);
        std::fill(tmp_path.begin(), tmp_path.end(), candidate);
        insertWanted(wantedList, end, {multiple * candidate, {tmp_path}});

        for (auto wanted : wantedList) {
          wanted.value += multiple * candidate; // wanted is a copy
          for (auto &path : wanted.paths) {
            path.insert(path.begin(), tmp_path.begin(),
                        tmp_path.end()); // path is not a copy
          }
          insertWanted(wantedList, end, wanted);
        }
      }
    }

    auto it = std::find(wantedList.begin(), wantedList.end(), target);
    if (it == wantedList.end()) {
      return {{}};
    }
    return it->paths;
  }

private:
  void insertWanted(std::vector<Wanted> &wantedList, int end,
                    const Wanted &wanted) {
    auto it = std::find(wantedList.begin(), wantedList.begin() + end, wanted);
    if (end >=0 && it != wantedList.begin() + end) {
      it->paths.insert(it->paths.end(), wanted.paths.begin(),
                       wanted.paths.end());
    } else {
      wantedList.push_back(wanted);
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
}
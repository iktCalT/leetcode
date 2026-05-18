#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
  int minJumps(std::vector<int>& arr) {
    // BFS
    // Actions: 1. left 2. right 3. same value

    // Jump to same value: create a hash table
    //     key: value value: indexes with same value
    std::unordered_map<int, std::vector<int>> checkTable;
    for (int i = 0; i < arr.size(); i++) {
      auto it = checkTable.find(arr[i]);
      if (it == checkTable.end()) {
        checkTable.emplace(arr[i], std::vector<int>{i});
      } else {
        // If consecutive, only store the first and last two
        if (i >= 2 && arr[i] == arr[i - 1] && arr[i] == arr[i - 2]) {
          checkTable[arr[i]].back() = i;
        } else {
          checkTable[arr[i]].push_back(i);
        }
      }
    }

    // Start to jump
    int count = 0;
    if (arr.size() == 1) return count;

    std::vector<bool> visited(arr.size(), false);
    std::queue<int> currentQueue;
    currentQueue.push(0);
    visited[0] = true;

    bool reached = false;
    while (true) {
      ++count;
      std::queue<int> nextQueue;

      while (!currentQueue.empty()) {
        int curi = currentQueue.front();
        currentQueue.pop();

        if (curi >= 1 && !visited[curi - 1]) {
          nextQueue.push(curi - 1);
          visited[curi - 1] = true;
        }

        if (curi + 1 == arr.size() - 1) {
          reached = true;
          break;
        }
        if (curi < arr.size() - 1 && !visited[curi + 1]) {
          nextQueue.push(curi + 1);
          visited[curi + 1] = true;
        }

        for (int nexti : checkTable[arr[curi]]) {
          if (nexti == arr.size() - 1) {
            reached = true;
            break;
          }
          if (!visited[nexti]) {
            nextQueue.push(nexti);
            visited[nexti] = true;
          }
        }
        checkTable.erase(arr[curi]);
      }

      if (reached == true) {
        break;
      }
      currentQueue = std::move(nextQueue);
    }

    return count;
  }
};

int main() {
  Solution demo;
  std::vector<int> arr{100,-23,-23,404,100,23,23,23,3,404};
  std::cout << demo.minJumps(arr) << std::endl;
}
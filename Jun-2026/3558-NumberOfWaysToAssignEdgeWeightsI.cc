#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int assignEdgeWeights(vector<vector<int>>& edges) {
    // Notice that the first edge could not be connected to root (1)
    // and upper node could be the second element. 
    // e.g. [[4,3],[3,5],[2,1],[3,1]]
    // 1. find maximum depth
    // 2. calculate
    
    // Use unordered_map to record the neighbors of each node
    unordered_map<int, vector<int>> map;
    for (vector<int> edge : edges) {
      if (map.contains(edge[0])) {
        map[edge[0]].push_back(edge[1]);
      } else {
        map.insert({edge[0], {edge[1]}});
      }
      if (map.contains(edge[1])) {
        map[edge[1]].push_back(edge[0]);
      } else {
        map.insert({edge[1], {edge[0]}});
      }
    }

    // calculate depth with BFS
    int depth = -1;
    queue<int>* working_que = new queue<int>; 
    queue<int>* waiting_que = new queue<int>;
    waiting_que->push(1);
    while (!waiting_que->empty()) {
      ++depth; // initial value: -1 + 1 = 0
      // swap working and waiting queues
      auto tmp = working_que;
      working_que = waiting_que;
      waiting_que = tmp;

      while (!working_que->empty()) {
        int parent = working_que->front();
        working_que->pop();
        for (int child : map[parent]) {
          waiting_que->push(child);
          // remove parent node from child
          quickErase(map[child], parent);
        }
      }
    }
    delete working_que;
    delete waiting_que;

    // Calculate ans
    return calculateCombinations(depth);
  }

private:
  void quickErase(vector<int>& vec, int val) {
    auto it = find(vec.begin(), vec.end(), val);
    // Don't need to verify if val exists, it must exist
    *it = *(vec.rbegin());
    vec.pop_back();
  }

  inline int calculateCombinations(int n) {
    // (n 1) + (n 3) + (n 5) + ...

    // If n is odd, e.g. n = 7
    // (7 1) + (7 3) + (7 5) + (7 7) = (7 6) + (7 4) + (7 2) + (7 0)
    // As we know, (7 0) + (7 1) + ... + (7 7) = 2 ^ 7
    // So, if n is odd, the answer is 2 ^ n / 2 = 2 ^ (n - 1)

    // If n is even, e.g. n = 8
    // answer is 2 ^ 7, 
    // if there are odd number of ones in previous 7 steps, the last step is 2
    // if there are even number of ones in previous 7 steps, the last step is 1

    // In summary, the answer is 2 ^ (n - 1)
    // However, n <= 10^5, meaning 2 ^ (n - 1) will easily go out of double's scope
    
    // Use Fast Modular Exponentiation algorithm 
    // https://courses.cs.washington.edu/courses/cse311/21sp/resources/reference-modular-exponentiation.pdf
    // if a = k1 * m + r1, b = k2 * m + r2 
    // (a * b) % m = (k1 * k2 * m^2 + (k1*r2 + k2*r1) * m + r1 * r2) % m
    // = r1 * r2 = (a % m) * (b % m)
    // If n in binary is (1001), then 2 ^ n can be written as 2 ^ (1000) * 2 ^ (0001)
    // So, (2 ^ n) % m = (2 ^ (0001) % m) * (2 ^ (1000) % m)

    --n; // n = n-1
    long long result = 1;
    int m = pow(10, 9) + 7;
    long long r = 2 % m;
    while (n != 0) {
      if (n % 2) {
        result = (result * r) % m; // result must be long long
      }
      r = (r * r) % m; // r must be long long
      n = n >> 1;
    }
    return result;
  }
};


struct NodeInfo {
  int depth; // we can delete this if we use two queues
  vector<int> neighbors; // parent or children
};

class Solution0 {
public:
  int assignEdgeWeights(vector<vector<int>>& edges) {
    // Notice that the first edge could not be connected to root (1)
    // and upper node could be the second element. 
    // e.g. [[4,3],[3,5],[2,1],[3,1]]
    // 1. find maximum depth
    // 2. calculate
    
    // Use unordered_map to record the neighbors of each node
    unordered_map<int, NodeInfo> map;
    for (vector<int> edge : edges) {
      if (map.contains(edge[0])) {
        map[edge[0]].neighbors.push_back(edge[1]);
      } else {
        map.emplace(edge[0], NodeInfo{-1, {edge[1]}});
      }
      if (map.contains(edge[1])) {
        map[edge[1]].neighbors.push_back(edge[0]);
      } else {
        map.emplace(edge[1], NodeInfo{-1, {edge[0]}});
      }
    }

    // calculate depth with BFS
    int max_depth = 0;
    map[1].depth = 0;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
      int parent = que.front();
      que.pop();
      for (int child : map[parent].neighbors) {
        que.push(child);
        map[child].depth = map[parent].depth + 1;
        max_depth = map[child].depth;
        // remove parent node from child
        quickErase(map[child].neighbors, parent);
      }
    }

    // Calculate ans
    return calculateCombinations(max_depth);
  }

private:
  void quickErase(vector<int>& vec, int val) {
    auto it = find(vec.begin(), vec.end(), val);
    // Don't need to verify if val exists, it must exist
    *it = *(vec.rbegin());
    vec.pop_back();
  }

  inline int calculateCombinations(int n) {
    // (n 1) + (n 3) + (n 5) + ...

    // If n is odd, e.g. n = 7
    // (7 1) + (7 3) + (7 5) + (7 7) = (7 6) + (7 4) + (7 2) + (7 0)
    // As we know, (7 0) + (7 1) + ... + (7 7) = 2 ^ 7
    // So, if n is odd, the answer is 2 ^ n / 2 = 2 ^ (n - 1)

    // If n is even, e.g. n = 8
    // answer is 2 ^ 7, 
    // if there are odd number of ones in previous 7 steps, the last step is 2
    // if there are even number of ones in previous 7 steps, the last step is 1

    // In summary, the answer is 2 ^ (n - 1)
    // However, n <= 10^5, meaning 2 ^ (n - 1) will easily go out of double's scope
    
    // Use Fast Modular Exponentiation algorithm 
    // https://courses.cs.washington.edu/courses/cse311/21sp/resources/reference-modular-exponentiation.pdf
    // if a = k1 * m + r1, b = k2 * m + r2 
    // (a * b) % m = (k1 * k2 * m^2 + (k1*r2 + k2*r1) * m + r1 * r2) % m
    // = r1 * r2 = (a % m) * (b % m)
    // If n in binary is (1001), then 2 ^ n can be written as 2 ^ (1000) * 2 ^ (0001)
    // So, (2 ^ n) % m = (2 ^ (0001) % m) * (2 ^ (1000) % m)

    --n; // n = n-1
    long long result = 1;
    int m = pow(10, 9) + 7;
    long long r = 2 % m;
    while (n != 0) {
      if (n % 2) {
        result = (result * r) % m; // result must be long long
      }
      r = (r * r) % m; // r must be long long
      n = n >> 1;
    }
    return result;
  }
};

int main() {
  Solution demo;
  vector<vector<int>> vec {{1,2}, {2,3},{3,4},{4,5},{5,6},{6,7},{7,8}};
  std::cout << demo.assignEdgeWeights(vec) << "\n";
}
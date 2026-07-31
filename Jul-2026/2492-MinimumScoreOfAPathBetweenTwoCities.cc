#include <deque>
#include <iostream>
#include <vector>

using namespace std;

struct Next {
  int city;
  int dist;
};

class Solution {
public:
  int minScore(int n, vector<vector<int>>& roads) {
    // 2 <= n <= 10^5, 1 <= distance <= 10^4
    // So, sum of distance won't exceed INT_MAX -> no overflow
    
    // map[i]: cities adjacent to i
    vector<vector<Next>> map(n + 1);

    for (const vector<int>& road : roads) {
      map[road[0]].emplace_back(road[1], road[2]);
      map[road[1]].emplace_back(road[0], road[2]);
    }

    vector<int> min_dist(n + 1, INT_MAX);
    deque<int> que;
    que.push_back(1); // add city 1
    while (!que.empty()) {
      int cur = que.front();
      que.pop_front();

      for (const Next next : map[cur]) {
        int new_dist = min(next.dist, min_dist[cur]);
        int& old_dist = min_dist[next.city];
        if (new_dist >= old_dist) continue;

        if (old_dist == INT_MAX) 
          que.push_back(next.city);
        else
          que.push_front(next.city);
        
        old_dist = new_dist;
      }
    }
    return min_dist[n];
  }
};

int main() {
  Solution demo;
  vector<vector<int>> roads{{1,2,9},{2,3,6},{2,4,5},{1,4,7}};
  std::cout << demo.minScore(4, roads) << "\n";
}
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution { // 3ms
public:
  int maxIceCream(vector<int>& costs, int coins) {
    long long lcoins = coins;
    // Counting sort
    long long max_val = *max_element(costs.begin(), costs.end());
    vector<long long> cnt(max_val + 1, 0); // 1 <= costs[i] <= max_val
    for (const int cost : costs) {
      ++cnt[cost];
    }

    int ans = cnt[0]; // should be 0
    for (int i = 1; i <= min(lcoins, max_val); ++i) { 
                      // max_val + 1 == cnt.size()
      ans += min(cnt[i], lcoins / i);
      lcoins -= cnt[i] * i; // cnt[i] * i can up to 10^10 > INT_MAX
    }
    return ans;
  }
};

class Solution1 { // even slower, 201ms
public:
  int maxIceCream(vector<int>& costs, int coins) {
    // Counting sort
    map<int, int> count;
    for (const int& cost : costs) {
      if (count.contains(cost)) ++count[cost];
      else count.emplace(cost, 1);
    }

    int ans = 0;
    for (const auto& [cost, cnt] : count) {
      int need = coins / cost;
      if (need >= cnt) {
        coins -= cost * cnt;
        ans += cnt;
      } else {
        coins -= need * cost;
        ans += need;
        break;
      }
    }
    return ans;
  }

};

class Solution0 { // 35ms
public:
  int maxIceCream(vector<int>& costs, int coins) {
    sort(costs.begin(), costs.end());
    int cnt = 0;
    for (const int& cost : costs) {
      if (cost <= coins) {
        coins -= cost;
        ++cnt;
      } else {
        break;
      }
    }
    return cnt;
  }
};

int main() {
  Solution demo;
  vector<int> costs{1,3,2,4,1};
  std::cout << demo.maxIceCream(costs, 7) << "\n";
}
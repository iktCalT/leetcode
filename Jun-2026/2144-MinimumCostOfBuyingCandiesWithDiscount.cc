#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int minimumCost(vector<int>& cost) {
    // Sum the price, then subtract the prices of free ones
    // we found that the candies with 3rd, 6th, 9th... highest
    // prices can be subtracted. -> just add up 1,2,4,5,7,8,...

    int sum = 0;
    sort(cost.begin(), cost.end(), greater<int>());

    // branchless programming
    switch (cost.size() % 3) {
    case 1:
      cost.push_back(0);
    case 2:
      cost.push_back(0);
    default:
      // do nothing
    }
    for (int i = 0; i + 2 < cost.size(); i += 3) {
      sum += cost[i] + cost[i + 1];
    }

    return sum;
  }
};
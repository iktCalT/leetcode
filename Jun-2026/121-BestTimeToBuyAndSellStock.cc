#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    // DP
    int ans = INT_MIN;
    int min_price = INT_MAX;
    for (int price : prices) {
      min_price = min(min_price, price);
      ans = max(ans, price - min_price);
    }
    return ans;
  }
};
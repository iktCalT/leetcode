#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    // buy on every valley and sell on every peak
    int ans = 0;
    bool hold_stock = false;
    for (int i = 0; i + 1 < prices.size(); ++i) {
      if (prices[i] < prices[i + 1] && !hold_stock) {
        // buy
        ans -= prices[i];
        hold_stock = true;
      }
      if (prices[i] > prices[i + 1] && hold_stock) {
        // sell
        ans += prices[i];
        hold_stock = false;
      }
    }
    // last day
    if (hold_stock) ans += prices.back();

    return ans;
  }
};
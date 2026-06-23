#include <vector>

class Solution {
public:
  std::vector<int> finalPrices(std::vector<int>& prices) {
    for (int i = 0; i < prices.size(); ++i) {
      int price = prices[i];
      for (int j = i + 1; j < prices.size(); ++j) {
        if (prices[j] <= price) {
          prices[i] -=  prices[j];
          break;
        }
      }
    }
    return prices;
  }
};
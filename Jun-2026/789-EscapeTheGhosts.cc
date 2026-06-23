#include <vector>

class Solution {
public:
  bool escapeGhosts(std::vector<std::vector<int>>& ghosts, std::vector<int>& target) {
    // If any ghost can reach the target before (or at the same time as)
    // player, player cannot win
    int pd = abs(target[0]) + abs(target[1]); 
                        // player's distance to target

    for (const auto& g : ghosts) {
      if (abs(g[0] - target[0]) + abs(g[1] - target[1]) <= pd) {
        return false;
      }
    }

    return true;
  }
};
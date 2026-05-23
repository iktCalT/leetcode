#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int count = 0;
        int farthest = 0 + nums[0];
        int pos = 1;
        while (pos < nums.size()) {
            count++;
            if (farthest >= nums.size() - 1) break;
            goFarthest(pos, farthest, nums);
        }
        return count;
    }

private:
    inline void goFarthest(int& pos, int& farthest, const vector<int>& nums) {
        int bound = farthest;
        for ( ; pos <= bound && pos < nums.size(); pos++) {
            farthest = max(farthest, pos + nums[pos]);
            if (farthest >= nums.size() - 1) break; // make it faster
        }
    }
};

int main() {
  Solution demo;
  vector<int> nums{2,3,1,1,1,1};
  std::cout << demo.jump(nums) << std::endl;
}
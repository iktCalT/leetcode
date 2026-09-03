#include <vector>
using namespace std;

/* 0ms */
class Solution {
public:
  int minimumDeletions(vector<int>& nums) {
    int n = nums.size();
    // If they are the same one (only 1 elements in the vector) return 1
    if (n == 1) return 1;

    // Find out the positions of min and max (maybe multiple)
    int min_v = nums[0]; // 1 <= nums.length
    int max_v = nums[0];
    int min_pos = 0;
    int max_pos = 0;

    for (int i = 1; i < n; ++i) {
      int num = nums[i];
      if (num < min_v) {
        min_v = num;
        min_pos = i;
      } else if (num > max_v) {
        max_v = num;
        max_pos = i;
      }
    }

    // 4 conditions: both left; both right; min left max right; max left min right
    // Both left
    int ans = max(min_pos + 1, max_pos + 1);
    // Both right
    ans = min(ans, max(n - min_pos, n - max_pos));
    // Max left min right
    // Don't worry about if max left is on the right of min right
    // Because we are caring about minimum ans. It won't influence ans
    ans = min(ans, max_pos + 1 + n - min_pos);
    // Min left max right
    ans = min(ans, min_pos + 1 + n - max_pos);

    return ans;
  }
};

/* 4ms */
class Solution0 {
public:
  int minimumDeletions(vector<int>& nums) {
    // This solution doesn't assume "The integers in nums are distinct."

    int n = nums.size();
    // If they are the same one (only 1 elements in the vector) return 1
    if (n == 1) return 1;

    // Find out the positions of min and max (maybe multiple)
    int min_v = nums[0]; // 1 <= nums.length
    int max_v = nums[0];
    pair<int, int> min_pos(0, 0);
    pair<int, int> max_pos(0, 0);

    for (int i = 1; i < n; ++i) {
      int num = nums[i];
      if (num < min_v) {
        min_v = num;
        min_pos.first = i;
        min_pos.second = i;
      } else if (num == min_v) {
        min_pos.second = i;
      }

      if (num > max_v) {
        max_v = num;
        max_pos.first = i;
        max_pos.second = i;
      } else if (num == max_v) {
        max_pos.second = i;
      }
    }

    // 4 conditions: both left; both right; min left max right; max left min right
    pair<int, int> min_dis(min_pos.first + 1, n - min_pos.second);
    pair<int, int> max_dis(max_pos.first + 1, n - max_pos.second);

    // Both left
    int ans = max(min_dis.first, max_dis.first);
    // Both right
    ans = min(ans, max(min_dis.second, max_dis.second));
    // Max left min right
    // Don't worry about if max left is on the right of min right
    // Because we are caring about minimum ans. It won't influence ans
    ans = min(ans, max_dis.first + min_dis.second);
    // Min left max right
    ans = min(ans, min_dis.first + max_dis.second);

    return ans;
  }
};
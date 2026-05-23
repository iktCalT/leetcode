#include <map>
class Solution {
public:
    int climbStairs(int n) {
      if (n <= 2) {
        return n;
      }
      int odd = 1;
      int even = 2;
      for (int i = 3; i <= n; i++) {
        if (i % 2) {
          odd += even;
        } else {
          even += odd;
        }
      }
      return n%2 ? odd : even;
    }

    int climbStairs_slower(int n) {
      std::map<int, int> notebook;
      notebook.emplace(1,1);
      notebook.emplace(2,2);
      for (int i = 3; i <= n; i++) {
        notebook.emplace(i, notebook[i - 1] + notebook[i - 2]);
      }
      return notebook[n];
    }
};
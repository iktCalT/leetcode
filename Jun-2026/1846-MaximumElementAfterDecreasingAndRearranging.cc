#include <vector>
using namespace std;

class Solution { // 7ms
public:
  int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int ans = 0;
    for (int i = 0; i < arr.size(); ++i) {
      if (arr[i] > ans) ++ans;
    }
    return ans;
  }
};
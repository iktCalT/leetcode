#include <algorithm>
#include <vector>
using namespace std;

/* 0ms */
class Solution {
public:
  int maximumProduct(vector<int>& nums) {
    // I need 5 elements: top 3 greatest, and top 2 smallest
    array<int, 3> maximum{INT_MIN, INT_MIN, INT_MIN};
    array<int, 2> minimum{INT_MAX, INT_MAX};
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int num = nums[i];
      if (num > maximum[0]) {
        maximum[2] = maximum[1];
        maximum[1] = maximum[0];
        maximum[0] = num;
      } else if (num > maximum[1]) {
        maximum[2] = maximum[1];
        maximum[1] = num;
      } else if (num > maximum[2]) {
        maximum[2] = num;
      }
      
      // Don't use "else if", because maximum and minimum may have overlap 
      if (num < minimum[0]) {
        minimum[1] = minimum[0];
        minimum[0] = num;
      } else if (num < minimum[1]) {
        minimum[1] = num;
      }
    }

    // After observing Solution0, we can notice that there are 
    // only 2 possible answers: maximum[0] * maximum[1] * maximum[2]
    // or maximum[0] * minimum[0] * minimum[1]
    return max(maximum[0] * maximum[1] * maximum[2],
                maximum[0] * minimum[0] * minimum[1]);
  }
};

/* 9ms */
class Solution0 {
public:
  int maximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    if (nums.back() <= 0) {
      // all elements <= 0
      return nums[n - 1] * nums[n - 2] * nums[n - 3];
    } else {
      int max_two = max(nums[0] * nums[1], nums[n - 2] * nums[n - 3]);
        // maximum product of two elements (except nums[n - 1])
      return max_two * nums[n - 1];
    }
  }
};
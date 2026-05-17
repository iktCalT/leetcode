#include <vector>

using namespace std;

class Solution {
public:
  bool canReach(vector<int> &arr, int start) {
    // DFS
    // arr[start] < 0 means "reached"
    if (start < 0 || start >= arr.size() || arr[start] < 0)
      return false;

    if (arr[start] == 0)
      return true;
    int current = arr[start];
    arr[start] = -1; // mark this position as "reached" before calling

    if (canReach(arr, start + current))
      return true;
    if (canReach(arr, start - current))
      return true;

    return false;
  }
};
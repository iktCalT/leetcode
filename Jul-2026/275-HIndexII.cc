#include <vector>
using namespace std;

class Solution {
public:
  int hIndex(vector<int>& citations) {
    // Binary search, find the last i, 
    // where citations[i] >= n - i
    // Notice that citations[i] - n + i is ascending
    // That's why we can use binary search
    // Then, hindex = n - i
    int n = citations.size();
    int lo = -1;
    int hi = n;
    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;
      if (citations[mid] >= n - mid) {
        hi = mid;
      } else {
        lo = mid;
      }
    }
    // i = hi, return n - i;
    return citations.size() - hi;
  }
};
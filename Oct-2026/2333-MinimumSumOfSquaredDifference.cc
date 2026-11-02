#include <functional>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

// 43ms
class Solution {
public:
  long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
    // Every time, make the greatest max(a) smaller
    // (where a == |nums1[i]-nums2[i]|)
    // Becasue a^2 - (a-1)^2 = 2*a - 1, the greater a, 
    // the greater improvement
    // k1 and k2 are same, we only care about k1+k2

    int n = nums1.size();
    map<long long, int, greater<int>> diffs; // key: abs(diff); value: count
    for (int i = 0; i < n; ++i) {
      ++diffs[abs(nums1[i] - nums2[i])];
    }
    ++diffs[0];
    
    int k = k1 + k2;
    auto it = diffs.begin();
    long long ans = 0;
    for (; next(it) != diffs.end(); ++it) {
      static int res = 0;
      auto& [d, c] = *it;
      auto& [nd, nc] = *next(it);
      if (c * (d - nd) <= k) {
        k -= c * (d - nd);
        nc += c;
        c = 0;
      } else {
        // k % c       of them  d -> d - (k / c + 1)
        // c - (k % c) of them  d -> d - (k / c)
        ans += (k % c) * (d - (k / c + 1)) * (d - (k / c + 1))
             + (c - (k % c)) * (d - (k / c)) * (d - (k / c));
        c = 0;
        k = 0;
        break;
      }
    }
    ++it;

    for (; it != diffs.end(); ++it) {
      auto& [diff, cnt] = *it;
      ans += cnt * diff * diff;
    }
    return ans;
  }
};

// 65ms
class Solution1 {
public:
  long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
    // Every time, make the greatest max(a) smaller
    // (where a == |nums1[i]-nums2[i]|)
    // Becasue a^2 - (a-1)^2 = 2*a - 1, the greater a, 
    // the greater improvement
    // k1 and k2 are same, we only care about k1+k2

    int n = nums1.size();
    unordered_map<int, int> diffs_unordered; // key: abs(diff); value: count
    for (int i = 0; i < n; ++i) {
      ++diffs_unordered[abs(nums1[i] - nums2[i])];
    }
    ++diffs_unordered[0];

    map<int, int, greater<int>> diffs (diffs_unordered.begin(), diffs_unordered.end());
    
    int k = k1 + k2;
    auto it = diffs.begin();
    long long ans = 0;
    for (; next(it) != diffs.end(); ++it) {
      static int res = 0;
      auto& [d, c] = *it;
      auto& [nd, nc] = *next(it);
      if ((long long)c * (d - nd) <= k) {
        k -= c * (d - nd);
        nc += c;
        c = 0;
      } else {
        // k % c       of them  d -> d - (k / c + 1)
        // c - (k % c) of them  d -> d - (k / c)
        ans += (long long)(k % c) * (d - (k / c + 1)) * (d - (k / c + 1))
             + (long long)(c - (k % c)) * (d - (k / c)) * (d - (k / c));
        c = 0;
        k = 0;
        break;
      }
    }
    ++it;

    for (; it != diffs.end(); ++it) {
      auto& [diff, cnt] = *it;
      ans += (long long) cnt * diff * diff;
    }
    return ans;
  }
};

// 55ms
class Solution0 {
public:
  long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
    // Every time, make the greatest max(a) smaller
    // (where a == |nums1[i]-nums2[i]|)
    // Becasue a^2 - (a-1)^2 = 2*a - 1, the greater a, 
    // the greater improvement
    // k1 and k2 are same, we only care about k1+k2

    int n = nums1.size();
    map<int, int, greater<int>> diffs; // key: abs(diff); value: count
    for (int i = 0; i < n; ++i) {
      ++diffs[abs(nums1[i] - nums2[i])];
    }
    ++diffs[0];
    
    int k = k1 + k2;
    auto it = diffs.begin();
    long long ans = 0;
    for (; next(it) != diffs.end(); ++it) {
      static int res = 0;
      auto& [d, c] = *it;
      auto& [nd, nc] = *next(it);
      if ((long long)c * (d - nd) <= k) {
        k -= c * (d - nd);
        nc += c;
        c = 0;
      } else {
        // k % c       of them  d -> d - (k / c + 1)
        // c - (k % c) of them  d -> d - (k / c)
        ans += (long long)(k % c) * (d - (k / c + 1)) * (d - (k / c + 1))
             + (long long)(c - (k % c)) * (d - (k / c)) * (d - (k / c));
        c = 0;
        k = 0;
        break;
      }
    }
    ++it;

    for (; it != diffs.end(); ++it) {
      auto& [diff, cnt] = *it;
      ans += (long long) cnt * diff * diff;
    }
    return ans;
  }
};
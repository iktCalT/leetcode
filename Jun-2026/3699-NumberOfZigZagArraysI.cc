#include <vector>
using namespace std;

const int mod = 1e9 + 7;

class Solution { // 479 ms
public:
  int zigZagArrays(int n, int l, int r) {
    if (l != 1) return zigZagArrays(n, 1, r - l + 1);

    // dp[i][dir][x], i: length, dir: direction, x: ending number
    // That's a n * 2 * r array
    // Actually, we only need 2 arrays for i and i - 1
    vector<vector<vector<int>>> dp (2, 
               vector<vector<int>> (2, 
                       vector<int> (r + 1)));
    
    int cur = 1 % 2;
    // when i == 1 (use 2 loops to make use of spacial locality)
    for (int x = 1; x <= r; ++x) dp[cur][0][x] = 1;
    for (int x = 1; x <= r; ++x) dp[cur][1][x] = 1;
    

    // increase i
    for (int i = 2; i <= n; ++i) { // i + 1: from 2 to n
      cur = i % 2; // cur: current; previous: 1 - cur
      // up
      // x == 1, px from 2 to r; x == 2, px from 3 to r ... (px: previous x)
      dp[cur][1][r] = 0;
      for (int x = r - 1; x >= 1; --x) {
        dp[cur][1][x] = dp[cur][1][x + 1] + dp[1 - cur][0][x + 1];
        dp[cur][1][x] %= mod;
      }

      // down
      // x == 1, px no choice; x == 2, px from 1 to 1; ...
      dp[cur][0][1] = 0;
      for (int x = 2; x <= r; ++x) {
        dp[cur][0][x] = dp[cur][0][x - 1] + dp[1 - cur][1][x - 1];
        dp[cur][0][x] %= mod;
      }
    }

    int ans = 0;
    // Two loops: spacial locality
    for (int x = 1; x <= r; ++x) {
      ans += dp[cur][0][x];
      ans %= mod;
    }
    for (int x = 1; x <= r; ++x) {
      ans += dp[cur][1][x];
      ans %= mod;
    }

    return ans;
  }
};

class Solution1 { // 819 ms
public:
  int zigZagArrays(int n, int l, int r) {
    if (l != 1) return zigZagArrays(n, 1, r - l + 1);

    // dp[i][dir][x], i: length, dir: direction, x: ending number
    // That's a n * 2 * r array
    vector<vector<vector<int>>> dp (n + 1, 
               vector<vector<int>> (2, 
                       vector<int> (r + 1, 0)));
    
    // when i == 1
    for (int x = 1; x <= r; ++x) {
      dp[1][0][x] = 1;
      dp[1][1][x] = 1;
    }


    // increase i
    for (int i = 2; i <= n; ++i) { // i + 1: from 2 to n
      // up
      // x == 1, px from 2 to r; x == 2, px from 3 to r ... (px: previous x)
      for (int x = r - 1; x >= 1; --x) {
        dp[i][1][x] = dp[i][1][x + 1] + dp[i - 1][0][x + 1];
        dp[i][1][x] %= mod;
      }

      // down
      // x == 1, px no choice; x == 2, px from 1 to 1; ...
      for (int x = 2; x <= r; ++x) {
        dp[i][0][x] = dp[i][0][x - 1] + dp[i - 1][1][x - 1];
        dp[i][0][x] %= mod;
      }
    }

    int ans = 0;
    for (int x = 1; x <= r; ++x) {
      ans += dp[n][0][x];
      ans %= mod;
      ans += dp[n][1][x];
      ans %= mod;
    }

    return ans;
  }
};

/* 
  If we know g(n, m) is the number of zig zag arrays
  formed by elements [1, m] ** and all elemets are used at lease once**

  Then zigZagArrays(n, m) is the number of zig zag arrays form by [1, m]
  zigZagArrays(n, m) = (m 1) * g(n, 1) + ... + (m i) * g(n, i) + ... + (m m) * g(n, m)
  Where (m i) is the combination number of choosing i balls from m balls

  zigZagArrays(n, m+1) 
    = (m+1 1) * g(n, 1) + ... + (m+1 i) * g(n, i) + ... + (m+1 m+1) * g(n, m+1)

 */

class Solution0 { // TLE
public:
  int zigZagArrays(int n, int l, int r) {
    if (l != 1) return zigZagArrays(n, 1, r - l + 1);

    // dp[i][dir][x], i: length, dir: direction, x: ending number
    // That's a n * 2 * r array
    vector<vector<vector<int>>> dp (n + 1, 
               vector<vector<int>> (2, 
                       vector<int> (r + 1, 0)));
    
    // when i == 1
    for (int x = 1; x <= r; ++x) {
      dp[1][0][x] = 1;
      dp[1][1][x] = 1;
    }


    // increase i
    for (int i = 1; i < n; ++i) { // i + 1: from 2 to n
      for (int x = 1; x <= r; ++x) { // x: from 1 to r
        // down
        for (int nx = 1; nx < x; ++nx) { // nx: next x
          dp[i + 1][1][nx] += dp[i][0][x];
          dp[i + 1][1][nx] %= mod;
        }

        // up
        for (int nx = x + 1; nx <= r; ++nx) {
          dp[i + 1][0][nx] += dp[i][1][x];
          dp[i + 1][0][nx] %= mod;
        }
      }
    }

    int ans = 0;
    for (int x = 1; x <= r; ++x) {
      ans += dp[n][0][x];
      ans %= mod;
      ans += dp[n][1][x];
      ans %= mod;
    }
    return ans;
  }
};


/* 
class Solution {
private:
  const int m = 1e9 + 7;
public:
  int zigZagArrays(int n, int l, int r) {
    // We need at least 2 different elements to form a zigZagArray
    if (l == r) return 0;
    // zigZagArrays(n, l, r) == zigZagArrays(n, 0, r - l)
    // written as zigZagArrays(n, r - l)
    return zigZagArrays(n, r - l);
  }
  
  private:
  int zigZagArrays(int n, int r) {
    // Let's call zigZagArrays(n, r) as f(n, r): size n zigzag array
    // with elements in range [0, r]

    // And let's assume in all f(n, r) arrays, all those starts with i
    // are forming a subset called g(i, n, r)
    // e.g. f(3, 2) has 10 arrays: 
    // 010, 020, 021        -> g(0, 3, 2), all starts with 0
    // 121, 120, 101, 102   -> g(1, 3, 2)
    // 212, 202, 201        -> g(2, 3, 2)

    // For f(n, r) arrays, half of them are starting by rising
    // and half of them are starting by decreasing. I will call
    // them rising arrays and decreasing arrays, respectively
    // Let's call the number of rising arrays of g(i, n, r)
    // r(i, n, r) and decreasing as d(i, n, r)
    // So, for f(3, 2)
    // 010, 020, 021        -> r(0, 3, 2), rising
    // 121, 120             -> r(1, 3, 2), rising
    // 101, 102             -> d(1, 3, 2), decreasing
    // 212, 202, 201        -> d(2, 3, 2), decreasing

    // To get f(4, 2)
    // _010, _020, _021       -> _ can be 1 or 2
    // _121, _120             -> _ can be 1
    // _101, _102             -> _ can be 0
    // _212, _202, _201       -> _ can be 1 or 0

    // So, f(n, r) = g(0, n, r) + g(1, n, r) + ... + g(r, n, r)
    // = r(0, n, r) + d(0, n, r) + r(1, n, r) + d(1, n, r) + ... + r(r, n, r) + g(r, n, r)
    // f(n + 1, r) = 0 * r(0, n, r) + r * d(0, n, r) + 1 * r(1, n, r) 
    //    + (r - 1) * d(1, n, r) + ... + r * r(r, n, r) + 0 * g(r, n, r)
  }
};
 */

/* ================== Incorrect solution ==================

// This solution only considers replacing peaks with new r
// e.g. for zigZagArrays(3, 1, 3) which is equivalent to f(3, 2) 
// we knew that f(3, 1) has [010], [101]
// this solution considers 
// [010], [020], [101], [201], [102], [202]
// but it doesn't consider
// [120], [021], [121], [212]
// Although we can fix it by adding some terms, it will make the 
// solution very complicated

class Solution {
private:
  const int m = 1e9 + 7;
public:
  int zigZagArrays(int n, int l, int r) {
    // We need at least 2 different elements to form a zigZagArray
    if (l == r) return 0;
    // zigZagArrays(n, l, r) == zigZagArrays(n, 0, r - l)
    // written as zigZagArrays(n, r - l)
    return zigZagArrays(n, r - l);
  }
  
  private:
  int zigZagArrays(int n, int r) {
    // I will call zigZagArrays(n, r) as f(n, r) in future.

    // For f(n, r) arrays, half of them are starting by rising
    // and half of them are starting by decreasing. I will call
    // them rising arrays and decreasing arrays, respectively
    // e.g. f(4, 2) has rising array: [0,2,1,2] it has corresponding
    // decreasing array [2-0, 2-2, 2-1, 2-2] == [2, 0, 1, 0]

    // So, if we can calculate f(n, r), then we can get f(n, r + 1) by
    // 1. Figure out how many elements in each **rising** array can be 
    //    replaced by element r + 1
    //   1.1. We know that all element in f(n, r) are less than or equal
    //        to r. So, all of them are strictly less than r + 1.
    //   1.2. So, all **peaks** can be replaced by r + 1.
    //        For example, f(4, 2) has rising array: [0,2,1,2]. If we need 
    //        to calculate f(4, 3), then [0, _, 1, _], where _ can be replaced
    //        by 3, so, we can add (2 ^ 2 - 1) to f(4, 3) for this array.
    //        -> Add (2 ^ [number of peaks] - 1) to f(n, r)
    //        -> Or just (2 ^ [number of peaks]) and don't add to f(n, r)
    //   1.3. We need to do 1.2 for each array of f(4, 2). Fortunately, the 
    //        peaks of each rising array are same.
    //
    // 2. Same as above, we also need to replace **peaks** in each decreasing 
    //    array. Rather than just multiply the result by 2.
    //   2.1. If n is even, there should be n / 2 peaks in each rising or 
    //        decreasing array
    //   2.2. If n is odd, there should be (n - 1) / 2 peaks in a rising array
    //        and (n + 1) / 2 peaks in a decreasing array.
    //   2.3. Considering the property of int, regardless of n's parity, 
    //        the number of peaks in a rising array is n / 2
    //        the number of peaks in a decreasing array is (n + 1) / 2

    // We also know f(n, 1) is always 2
    if (r == 1) return 2;

    int prev = zigZagArrays(n, r - 1);
    // Rising arrays
    int rising = prev / 2 * ((int) pow(2, n / 2));
    int decreasing = prev / 2 * ((int) pow(2, (n + 1) / 2));

    return rising + decreasing;
  }
};

*/
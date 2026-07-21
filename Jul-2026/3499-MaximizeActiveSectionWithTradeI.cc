#include <string>
#include <vector>
using namespace std;

/* 
 * Leetcode says it's wrong, but I think it's correct
 * Test case: "110011", "101", "1010010010011011100010100110111110010100010110110101111000001011101001010110101101000000111110010111111001110110001111111011110011000110011111101111010001000110001100001111110111000111111010100110111100000010110000000001010110110010111101100100011010011110101010011010101011010000101111101000111101110100101101110000010001101111000011110100110000001101"
 */
class Solution {
public:
  int maxActiveSectionsAfterTrade(string s) {
    vector<int> segs; //segments, first and last of '1's segs
    if (s[0] == '0') segs.push_back(0); // add a empty seg
    int n = s.size();

    char cur = s[0];
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == cur) {
        // segment continue growing
        ++cnt;
      } else {
        // next seg
        segs.push_back(cnt);
        cur = s[i];
        cnt = 1;
      }
    }
    if (cnt != 0) segs.push_back(cnt);

    // make sure first and last segments are segments of '1's
    if (s[n - 1] == '0') segs.push_back(0); 

    int m = segs.size();
    int ans = max(segs[0], segs[m - 1]); // in case s == "111111"
    // segs[0] and segs[m - 1] cannot be flipped!!
    // segs[1] and segs[m - 2] are '0's
    
    if (m < 5) return ans; // No flip

    int block = 0;
    for (int i = 0; i < 5; ++i) { // first flip-able seg
      block += segs[i];
    }
    ans = max(ans, block);
    if (m == 5) return ans;

    for (int i = 4; i < m - 2; i += 2) { // other flip-able seg of '1's
      block -= segs[i - 4] + segs[i - 3];
      block += segs[i + 1] + segs[i + 2];
      ans = max(ans, block);
    }

    return ans;
  }
};
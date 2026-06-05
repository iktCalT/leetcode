class Solution {
public:
  vector<int> grayCode(int n) {
    // 0000 
    // -> 0001 
    // -> 0011 -> 0010
    // -> 0110 -> 0111 -> 0101 -> 0100
    // -> 1100 -> 1101 -> 1111 -> 1110 -> 1010 -> 1011 -> 1001 -> 1000
   
    // if we get arr = grayCode(k), then grayCode(k+1) = arr.insert(arr.end(), 2^k + arr.reverse)
    
    vector<int> gc = {0};
    for (int i = 1; i <= n; ++i) {
      vector<int> copy = gc;
      reverse(copy.begin(), copy.end());
      for (int& num : copy) {
        num += 1 << (i - 1);
      }
      gc.insert(gc.end(), copy.begin(), copy.end());
    }
    return gc;
  }
};
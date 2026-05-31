class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        // 5: 0101, 6: 0110,7: 0111 -> 0100: 4
        int ans = 0; // all bits are 1
        for (int i = 0; i < 32; ++i) {
            if (right >> i == 0) break;
            if ((right - left) >> i > 0) continue;
            if ( ((left >> i) & 1) && ((right >> i) & 1) ) ans += 1 << i;
        }
        return ans;
    }
};
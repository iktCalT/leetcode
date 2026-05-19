class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0 || x == 1) return x; // If x is 0, then n > 0.
        if (n == 0) return 1;
        if (n < 0) return 1 / (x * myPow(x, -1-n)); // Incase n == INT_MIN

        // n > 0
        if (x == -1) return n % 2 ? -1 : 1;

        double ans = x;
        int i = 1;
        for (; i <= n / 2; i *= 2) {
            ans *= ans;
        } // ans = pow(x, i)
        if (i == n) return ans;

        return ans * myPow(x, n - i);
    }
};
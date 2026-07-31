class Solution { // 0ms, 8.4MB
public:
  int gcdOfOddEvenSums(int n) {
    int sum_odd = n * n;
    int sum_even = n * (n + 1);

    return gcd(sum_odd, sum_even);
  }

private:
  int gcd(int m, int M) {
    rank(m, M);
    while ((M / m) * m != M) {
      M = M - m;
      rank(m, M);
    }
    return m;
  }

  inline void rank(int& m, int& M) {
    if (M < m) {
      int tmp = M;
      M = m;
      m = tmp;
    }
  }
};

class Solution0 { // 0ms, 8.5MB
public:
  int gcdOfOddEvenSums(int n) {
    int sum_odd = n * n;
    int sum_even = n * (n + 1);

    return gcd(sum_odd, sum_even);
  }

private:
  int gcd(int a, int b) {
    if (a > b) return gcd(b, a);

    if ((b / a) * a == b) return a;

    return gcd(a, b - a);
  }
};
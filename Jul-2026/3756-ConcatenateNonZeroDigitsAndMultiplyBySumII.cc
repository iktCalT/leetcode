#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* Solution: prefixsum + precompute everything! */
class Solution {
public:
  vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
    // It can be divided into 2 questions
    // 1. How to get sum quickly? -> use prefix sum, sum of numbers
    // 2. How to get x quickly? 
    //    -> 2.1. Create a non-zero version of s
    //    -> 2.2. Get new start and new end quickly (another prefix sum, sum of zeros)
    //    -> 2.3. Precompute (a * b) % M = ((a % m) * (b % m)) % m
    //    -> 3.4. Precompute (pow(10, i)) % M

    int n = s.size();
    vector<int> prefix_sum(n + 1); // sum of numbers from s[0] to s[i] (exclusive)
    vector<int> prezero_sum(n + 1); // sum of zeros from s[0] to s[i] (exclusive)
    vector<long long> precompute_x{0}; // atoi(s[0] to s[i](exclusive)) % M
    vector<long long> precompute_pow10(n + 1); // pow(10, i) % M
    prefix_sum[0] = 0;
    prezero_sum[0] = 0;
    precompute_pow10[0] = 1;

    for (int i = 0; i < s.size(); ++i) {
      prefix_sum[i + 1] = prefix_sum[i] + s[i] - '0'; // it won't exceed 10^6 (< INT_MAX)
      prezero_sum[i + 1] = prezero_sum[i] + (s[i] == '0');
      if (s[i] != '0') {
        precompute_x.push_back((precompute_x.back() * 10) % M + s[i] - '0');
      }
      precompute_pow10[i + 1] = (precompute_pow10[i] * 10) % M;
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (const vector<int>& query : queries) {
      int sum = prefix_sum[query[1] + 1] - prefix_sum[query[0]];
      int start = query[0] - prezero_sum[query[0]];
      int end = query[1] - prezero_sum[query[1] + 1];

      long long x = precompute_x[end + 1] - (precompute_x[start] * precompute_pow10[end + 1 - start]) % M + M;
      ans.push_back((x * sum) % M);
    }

    return ans;
  }

private:
  const int M = 1e9+7;
};

/* Solution1: prefixsum -> TLE */
class Solution1 {
public:
  vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
    // It can be divided into 2 questions
    // 1. How to get sum quickly? -> use prefix sum, sum of numbers
    // 2. How to get x quickly? 
    //    -> 2.1. Create a non-zero version of s
    //    -> 2.2. Get new start and new end quickly (another prefix sum, sum of zeros)

    int n = s.size();
    vector<int> prefix_sum(n + 1); // sum of numbers from s[0] to s[i] (exclusive)
    vector<int> prezero_sum(n + 1); // sum of zeros from s[0] to s[i] (exclusive)
    prefix_sum[0] = 0;
    prezero_sum[0] = 0;    
    string s_without_0;

    for (int i = 0; i < s.size(); ++i) {
      prefix_sum[i + 1] = prefix_sum[i] + s[i] - '0'; // it won't exceed 10^6 (< INT_MAX)
      prezero_sum[i + 1] = prezero_sum[i] + (s[i] == '0');
      if (s[i] != '0') s_without_0 += s[i];
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (const vector<int>& query : queries) {
      int sum = prefix_sum[query[1] + 1] - prefix_sum[query[0]];
      int start = query[0] - prezero_sum[query[0]];
      int end = query[1] - prezero_sum[query[1] + 1];
      long long x = get_x(start, end, s_without_0);
      ans.push_back((x * sum) % M);
    }

    return ans;
  }

private:
  const int M = 1e9+7;
  long long get_x(int start, int end, const string& s_without_0) {
    long long x = 0;
    for (int i = start; i <= end; ++i) {
      x = (x * 10 + s_without_0[i] - '0') % M;
    }
    return x;
  }
};

/* --- Solution0: Segment tree -> TLE --- */
struct SegTreeNode {
  int start;
  int end;
  string x;
  SegTreeNode *left;
  SegTreeNode *right;

  static SegTreeNode *build(const string &s) {
    SegTreeNode *root = new SegTreeNode{
        0,
        (int)s.size() - 1,
    };
    for (int i = 0; i < s.size(); ++i) {
      char c = s[i];
      if (c == '0')
        continue;

      SegTreeNode *p = root;
      while (p->start != p->end) {
        p->x += c;
        int mid = (p->start + p->end) / 2;
        if (i <= mid) {             // go left
          if (p->left == nullptr) { // create new node
            p->left = new SegTreeNode{p->start, mid, {}};
          }
          p = p->left;
        } else { // go right
          if (p->right == nullptr) {
            p->right = new SegTreeNode{mid + 1, p->end, {}};
          }
          p = p->right;
        }
      }
      p->x = {c};
    }
    return root;
  }

  static string search(int start, int end, const SegTreeNode* const p) {
    // p could be nullptr, start could be less than p->start, 
    // and end could be greater than p->end because if
    // s[i] == '0', it won't be added to segment tree and
    // won't create nodes
    string result = {};
    if (p == nullptr) return ""; 
    if (start <= p->start && end >= p->end) 
      return p->x;
    
    int mid = (p->start + p->end) / 2;
    if (start <= mid) {
      result += search(start, min(end, mid), p->left);
    }
    if (end >= mid + 1) {
      result += search(max(start, mid + 1), end, p->right);
    }
    return result;
  }
};

class Solution0 {
public:
  vector<int> sumAndMultiply(string s, vector<vector<int>> &queries) {
    // Segment tree
    SegTreeNode *root = SegTreeNode::build(s);
    vector<int> ans;
    ans.reserve(queries.size());
    for (const vector<int>& query : queries) {
      string x = SegTreeNode::search(query[0], query[1], root);
      ans.push_back(x2result(x));
    }
    return ans;
  }

private:
  const int M = 1e9 + 7;
  int x2result(string x) {
    // x is a string without zeros
    // If we convert x to number (x_int),
    // it could be up to 10 ^ (10 ^ 5)!
    // sum could be up to 10 * 10^5 (< INT_MAX)

    // x_int is long long, so that x_int * 10 won't exceed limit
    // moreover, sum * (x_int % M) <= sum * M <= LLONG_MAX
    long long x_int = 0;
    int sum = 0;
    for (char c : x) {
      x_int = (x_int * 10 + c - '0') % M;
      sum += c - '0';
    }

    // x_int * sum <= (1e9+7) * (1e6) < LLONG_MAX
    return (x_int * sum) % M;
  }
};

int main() {
  Solution demo;
  vector<vector<int>> queries{{0, 7}, {1, 3}, {4, 6}};
  auto ans = demo.sumAndMultiply(
    "10203004",
    queries);
  for (const auto& item : ans) {
    std::cout << item << "\n";
  }

  // std::cout << demo.sumAndMultiply(
  //   "987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321987654321",
  //   queries)[0] - 124419042 << "\n";
}
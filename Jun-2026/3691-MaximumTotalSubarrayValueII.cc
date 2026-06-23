#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// cannot name it "TreeNode"
struct Node { // 64 bytes. (2 * n - 1) * 64 = 64 * 10 ^ 5 bytes = 6.4 Mb
  int lo;
  int hi;
  int min;
  int max;
  Node* left;
  Node* right;
  
  Node(int lo, int hi, int min, int max) 
    : lo(lo), hi(hi), min(min), max(max), left(nullptr), right(nullptr) {}
};

class Solution { // finished after reading editorial
public:
  long long maxTotalValue(vector<int>& nums, int k) {
    // Create a segment tree
    Node* root = new Node(0, nums.size() - 1, nums[0], nums[0]);
    for (int i = 0; i < nums.size(); ++i) {
      insertTreeNode(root, i, nums[i]);
    }

    // Add to queue
    // notice that value (max - min) of nums[i...j] must not be 
    // greater than value of nums[i...j+1]
    
    // So, initially, the maximum value must be in subarrays:
    // [0, n-1], [1, n-1], [2, n-1], ... , [n-2, n-1]
    // let's add them all to heap
    // If [0, n-1] is the greatest, after adding it to ans, 
    // we need to add its sequencer to the heap, which is [0, n-2]
    // Now, if [5,n-1] is the greatest, we need to add [5, n-2] to heap
    priority_queue<tuple<int, int, int>> que;
    long long ans = 0;
    for (int i = 0; i < nums.size(); ++i) {
      auto min_max = getMinMax(root, i, nums.size() - 1);
      // 0 <= nums[i] <= 10^9, max - min must be an int
      que.push({min_max.second - min_max.first, i, nums.size() - 1});
    }

    while (k > 0) {
      auto [val, start, end] = que.top();
      que.pop();
      ans += val;
      // add [start, end - 1]
      if (start < end) {
        auto min_max = getMinMax(root, start, end - 1);
        que.push({min_max.second - min_max.first, start, end - 1});
      }
      --k;
    }

    return ans;
  }

private:
  void insertTreeNode(Node* root, int pos, int val) {
    Node* p = root;
    while (p->lo != p->hi) { // while is not leaf
      p->max = max(p->max, val);
      p->min = min(p->min, val);

      int mid = (p->hi + p->lo) / 2;
      if (pos <= mid) {
        // go left
        if (!p->left) {
          p->left = new Node(p->lo, mid, val, val);
        }
        p = p->left;
      } else {
        // go right
        if (!p->right) {
          p->right = new Node(mid + 1, p->hi, val, val);
        }
        p = p->right;
      }
    }
  }

  pair<int, int> getMinMax(Node* subroot, int start, int end) {
    // Calculate the difference between max and min of subarray [start, end]
    // if (start > end) return {INT_MAX, INT_MIN};

    if (start == subroot->lo && end == subroot->hi) {
      return {subroot->min, subroot->max};
    }

    int mid = (subroot->lo + subroot->hi) / 2;
    if (end <= mid) return getMinMax(subroot->left, start, end);
    if (start > mid) return getMinMax(subroot->right, start, end);

    // lmm: left min max; rmm: right min max
    auto lmm = getMinMax(subroot->left, start, mid);
    auto rmm = getMinMax(subroot->right, mid + 1, end);
    return {min(lmm.first, rmm.first), max(lmm.second, rmm.second)};
  }
};

int main() {
  Solution demo;
  vector<int> nums{11, 8};
  std::cout << demo.maxTotalValue(nums, 2) << "\n";
}
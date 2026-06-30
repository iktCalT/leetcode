#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int countMajoritySubarrays(vector<int>& nums, int target) {
    // Brute force
    int size = nums.size();
    int ans = 0;
    for (int i = 0; i < size; ++i) {
      int cnt = 0;
      for (int j = i; j < size; ++j) {
        cnt += nums[j] == target ? 1 : -1;
        ans += cnt > 0;
      }
    }
    return ans;
  }
};

struct Node0 { // 2227ms, very slow
  int start;
  int end;
  int nt; // number of targets
  Node0* left; // [start, mid]
  Node0* right; // [mid + 1, end]

  Node0(int start, int end) 
    : start(start), end(end), nt(0), left(nullptr), right(nullptr) {}
};

class Solution0 {
public:
  int countMajoritySubarrays(vector<int>& nums, int target) {
    // Create a segment tree
    int size = nums.size();
    Node0* root = new Node0(0, size - 1);
    int cnt = 0;
    for (int i = 0; i < size; ++i) {
      bool is_target = nums[i] == target;
      cnt += is_target;   // don't need to look up this part in the future
      insertNode(i, is_target, root);
    }
  
    for (int i = 0; i < size; ++i) {
      for (int j = i + 1; j < size; ++j) { // don't add j == i case, already considered
        // Total: j - i + 1
        cnt += 2 * lookup(i, j, root) > (j - i + 1);
      }
    }

    return cnt;
  }

private:
  void insertNode(int index, bool is_target, Node0* p) {
    p->nt += is_target;
    if (p->start == p->end) return; // leaf node

    int mid = (p->start + p->end) / 2;
    if (index <= mid) {
      // left
      if (p->left == nullptr) {
        p->left = new Node0(p->start, mid);
      }
      insertNode(index, is_target, p->left);
    } else {
      // right
      if (p->right == nullptr) {
        p->right = new Node0(mid + 1, p->end);
      }
      insertNode(index, is_target, p->right);
    }
  }

  int lookup(int start, int end, const Node0* const p) {
    if (p->start == start && p->end == end) {
      return p->nt;
    }

    int mid = (p->start + p->end) / 2;
    if (start <= mid && end <= mid) {
      // only left part
      return lookup(start, end, p->left);
    } else if (start > mid && end > mid) {
      return lookup(start, end, p->right);
    } else {
      return lookup(start, mid, p->left) + lookup(mid + 1, end, p->right);
    }
  }
};

/* 

// Incorrect, e.g. for [3, 2, 3, 3], 
// it counts [3], [3], [3], [3, 3], [2, 3, 3], [3, 2, 3, 3]
// but misses [3, 2, 3]

struct Block {
  int nt; // number of target: how many consecutive targets
  int nnt; // number of not target: how man consecutive non-target on the right
};

class Solution {
public:
  int countMajoritySubarrays(vector<int>& nums, int target) {
    // If we have consecutive k targetsthen its left l elements
    // and right r elements, where l + r < k, can be a subarray 
    // with target as their majority elements

    // We also need to consider a special case: two separate 
    // consecutive targets can form a greater subarray

    // e.g. nums = {1,2,3,3,3,2,3,5,6,3,3,4}, target = 3
    // we have consecutive {3,3,3}, so 3 * {3}, 3 * {3,3}, {3,3,3}, 
    // {2,3,3,3}, {3,3,3,2}, {1,2,3,3,3}, {2,3,3,3,2}, {3,3,3,2,3}
    // {3,3,3,2,3,5} are desired subarrays
    int ans = 0;

    int nnt;
    for (nnt = 0; nnt < nums.size() && nums[nnt] != target; ++nnt) {}
    vector<Block> blocks = {{INT_MIN, nnt}};

    for (int i = nnt; i < nums.size();) {
      // if (nums[i] == target)
      int nt, nnt, j, k;
      for (j = i; j < nums.size() && nums[j] == target; ++j) {}
      nt = j - i;
      for (k = j; k < nums.size() && nums[k] != target; ++k) {}
      nnt = k - j;

      // Only targets: nt + (nt - 1) + ... + 1 - 1
      // don't include the whole block, it will be counted in helper()
      ans += (nt * (nt + 1)) / 2 - 1;

      ans += helper(nt, blocks.back().nnt, nnt);
      
      while (blocks.size() > 1 && nt + blocks.back().nt > blocks.back().nnt) {
        // combine
        nt = nt + blocks.back().nt - blocks.back().nnt;
        blocks.pop_back();
        ans += helper(nt, blocks.back().nnt, nnt);
      }

      blocks.emplace_back(nt, nnt);
      i = k;
    }
    return ans;
  }

private:
  int helper(int nt, int lnnt, int rnnt) {
    // l + r < n
    // lnnt: number of consecutive elements != target on the left
    // rnnt: number of consecutive elements != target on the right
    int cnt = 0;

    // consecutive targets + other
    lnnt = min(lnnt, nt - 1);
    // l from 0 to min(lnnt, nt - 1)
    for (int l = 0; l <= lnnt; ++l) {
      // r from 0 to min(nt - 1 - l, rnnt)
      cnt += 1 + min(nt - 1 - l, rnnt);
    }
    
    return cnt;
  }
};

*/

int main() {
  Solution demo;
  vector<int> nums{3,2,3,3};
  std::cout << demo.countMajoritySubarrays(nums, 3) << "\n";
}
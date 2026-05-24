/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class INF {
public:
  bool positive;
  explicit INF(bool positive) : positive(positive) {};
  friend bool operator>(INF& rhs, int) { return rhs.positive; }
  friend bool operator<(INF& rhs, int) { return !rhs.positive; }
  friend bool operator>=(INF& rhs, int) { return rhs.positive; }
  friend bool operator<=(INF& rhs, int) { return !rhs.positive; }
};

class Solution {
public:
  bool isValidBST(TreeNode *root) {
    // DFS
    // I need 2 functions, one is validateLeft, setting a upper bound
    // the other is validateRight, setting a lower bound

    if (!validateSub(root->left, root->val, INF(false)))
      return false;
    if (!validateSub(root->right, INF(true), root->val))
      return false;
    return true;
  }

private:
  // This test case hurts me [-2147483648,null,2147483647]
  template <typename T1, typename T2>
  bool validateSub(TreeNode *subroot, T1 ub, T2 lb) { // ub: upper bound
    if (subroot == nullptr)
      return true;
    if (ub <= subroot->val)
      return false;
    if (lb >= subroot->val)
      return false;
    if (!validateSub(subroot->left, subroot->val, lb))
      return false;
    if (!validateSub(subroot->right, ub, subroot->val))
      return false;
    return true;
  }
};
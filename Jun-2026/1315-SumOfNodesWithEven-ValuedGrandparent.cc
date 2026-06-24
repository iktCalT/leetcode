/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
* };
*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  int sumEvenGrandparent(TreeNode* root) {
    // DFS or BFS
    ans = 0;
    dfs(root, false, false);
    return ans;
  }

private:
  int ans;
  void dfs(TreeNode* node, bool even_parent, bool even_grandpa) {
    if (node == nullptr) return;

    if (even_grandpa) ans += node->val;
    // Children
    bool even = !(node->val % 2);
    dfs(node->left, even, even_parent);
    dfs(node->right, even, even_parent);
  }
};
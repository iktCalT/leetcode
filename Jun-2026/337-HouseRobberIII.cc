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

#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct MaxVal {
  int selected; // can be selected, but not necessarily to be selected
  int not_selected;

  MaxVal() {}
  MaxVal(int selected, int not_selected) 
    : selected(selected), not_selected(not_selected) {}
};

class Solution {
public:
  int rob(TreeNode* root) {
    // maximum value: 10^4 * 10^4 < INT_MAX, using int is enough
    // we need to track for each node:
    // 1. maximum value of its subtree if it can be selected 
    //        (of course, you can also choose not to select it)
    // 2. maximum value of its subtree if it cannot be selected not selected

    // DFS
    return dfs(root).selected;
  }

private:
  MaxVal dfs(TreeNode* subroot) {
    if (subroot == nullptr) {
      return MaxVal(0, 0);
    }

    MaxVal left = dfs(subroot->left);
    MaxVal right = dfs(subroot->right);

    MaxVal self;
    // MaxVal.selected >= MaxVal.not_selected
    self.not_selected = left.selected + right.selected;
    self.selected = std::max(self.not_selected, 
      subroot->val + left.not_selected + right.not_selected);
    
    return self;
  }
};
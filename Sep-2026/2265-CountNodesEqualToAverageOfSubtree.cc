/**
 * Definition for a binary tree node.
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
  int averageOfSubtree(TreeNode* root) {
    // postorder + DFS -> for each node
    // record sum and number of nodes 
    // (cannot record average, it's rounded)
    // of its subtree

    int ans = 0;
    dfs(ans, root);
    return ans;
  }

private:
  struct NodeInfo {int sum; int n;};

  NodeInfo dfs (int& ans, TreeNode* p) {
    if (p == nullptr) { // leaf
      return {0, 0};
    }

    NodeInfo left_info = dfs(ans, p->left);
    NodeInfo right_info = dfs(ans, p->right);

    int n = (left_info.n + right_info.n + 1);
    int sum = (p->val + left_info.sum + right_info.sum);

    if (p->val == sum / n) ++ans;

    return { sum, n };
  }
};
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

#include <vector>

using namespace std;

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
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildSubtree(0, 0, preorder.size(), preorder, inorder);
  }

private:
  int findInorderSubroot(int pstart, int istart, vector<int>& preorder, 
      vector<int>& inorder) {
    // return the distance between subroot and start in inorder
    int root_val = preorder[pstart];
    for (int i = istart; i < inorder.size(); ++i) {
      if (inorder[i] == root_val) {
        return i - istart;
      }
    }
    return -1; // this should not happen
  }

  TreeNode* buildSubtree(int pstart, int istart, int size,
      vector<int>& preorder, vector<int>& inorder) {
    if (size <= 0) return nullptr;
    TreeNode* subroot = new TreeNode(preorder[pstart]);
    if (size == 1) return subroot;

    int dist = findInorderSubroot(pstart, istart, preorder, inorder);
    subroot->left = buildSubtree(pstart + 1, istart, dist, preorder, inorder);
    subroot->right = buildSubtree(pstart + 1 + dist, istart + 1 + dist, size - dist - 1, preorder, inorder);
    return subroot;
  }
};
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

#include <map>
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
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    // The last element of postorder must be root (for each subtree)
    map<int, int> quickIn;
    for (int i = 0; i < inorder.size(); ++i) {
      quickIn.insert({inorder[i], i});
    }

    return buildSubtree(inorder.size() - 1, inorder.size() - 1,
        inorder.size(), inorder, postorder, quickIn);
  }

private:
  TreeNode* buildSubtree(int pe, int ie, int size,
      vector<int>& inorder, vector<int>& postorder,
      map<int, int>& quickIn) {
    // pe: postorder end; ie: inorder end
    if (size <= 0) return nullptr;
    TreeNode* subroot = new TreeNode(postorder[pe]);
    if (size == 1) return subroot;

    int r_size = ie - quickIn[subroot->val];
    subroot->right = buildSubtree(pe - 1, ie, 
        r_size, inorder, postorder, quickIn);
    int l_size = size - 1 - r_size;
    subroot->left = buildSubtree(pe - 1 - r_size, ie - 1 - r_size, 
        l_size, inorder, postorder, quickIn);
    return subroot;
  }
};
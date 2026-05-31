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

#include <unordered_map>
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

class Solution { // faster (0ms) because findInorderSubroot won't be called again and again
public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> quickFindIn;
    for (int i = 0; i < preorder.size(); ++i) {
      quickFindIn.insert({inorder[i], i});
    }

    return buildSubtree(0, 0, preorder.size(), preorder, inorder, quickFindIn);
  }

private:
  TreeNode* buildSubtree(int pstart, int istart, int size,
      vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& quickFindIn) {
    if (size <= 0) return nullptr;
    TreeNode* subroot = new TreeNode(preorder[pstart]);
    if (size == 1) return subroot;
    
    int dist = quickFindIn[preorder[pstart]] - istart;
    subroot->left = buildSubtree(pstart + 1, istart, dist, preorder, inorder, quickFindIn);
    subroot->right = buildSubtree(pstart + 1 + dist, istart + 1 + dist, size - dist - 1, preorder, inorder, quickFindIn);
    return subroot;
  }
};

class Solution2 { // same as above
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
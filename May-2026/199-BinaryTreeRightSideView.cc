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
    vector<int> rightSideView(TreeNode* root) {
        // I have to go through all nodes, in case there is a very deep branch
        // DFS

        exploreTreeNode(root, 0);
        return ans;
    }

private:
    vector<int> ans;
    
    void exploreTreeNode (TreeNode* p, int depth) {
        if (p == nullptr) return;
        if (ans.size() == depth) ans.push_back(p->val);

        // start from right node
        exploreTreeNode(p->right, depth + 1);
        exploreTreeNode(p->left, depth + 1);
    }
};
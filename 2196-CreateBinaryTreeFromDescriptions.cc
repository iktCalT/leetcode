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
class Solution {
public:
  TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
    // record all nodes with unordered map
    // notice that it's a binary tree of "unique" values
    unordered_map<int, TreeNode*> map;
    
    // insert all node in map
    for (auto& desc : descriptions) {
      map.emplace(desc[1], new TreeNode(desc[1]));
      }
    
    TreeNode* root;
    for (auto& desc : descriptions) {
      if (map.find(desc[0]) == map.end()) {
        // if not in map, its parent must be root
        map.emplace(desc[0], new TreeNode(desc[0]));
        root = map[desc[0]];
      }
      
      if (desc[2]) {
        // if isLeft
        map[desc[0]]->left = map[desc[1]];
      } else {
        map[desc[0]]->right = map[desc[1]];
      }
    }
    
    // there should be only one unremoved node, which is the root 
    return root;
  }
};
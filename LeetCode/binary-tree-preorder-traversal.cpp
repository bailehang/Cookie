/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ret;
        dfs(root, ret);
        return ret;
    }
private:
    void dfs(TreeNode *node, vector<int> &ret) {
        if (node == NULL) {
            return;
        }
        ret.push_back(node->val);
        dfs(node->left, ret);
        dfs(node->right, ret);
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
// preorder:  visit the root, and push right first to stack to store for later visitor after finish the left, and then push left, poop left to visit. ...
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> values;
        if (!root) return values;

        stack<TreeNode*> visited;
        visited.push(root);
        
        while (!visited.empty()) {
            TreeNode* curnode = visited.top();
            values.push_back(curnode->val);
            visited.pop();
            if (curnode->right) visited.push(curnode->right);
            if (curnode->left) visited.push(curnode->left);
        }
        return values;
    }
};